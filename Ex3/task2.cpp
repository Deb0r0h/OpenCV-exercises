#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

//return a Mat vector with the images in the path
vector<Mat> createVecImgFromSource(string path)
{
    vector<Mat> images;
    vector<string> fileNames;

    glob(path, fileNames);
    for (const auto& filename : fileNames) 
    {
        Mat image = imread(filename);
        images.push_back(image);      
    }
    return images;

}

//Make the union of two images and return it
Mat img1UnionImg2(Mat img1,Mat img2)
{
    int colsSum = img1.cols + img2.cols;
    int rowsSum = max(img1.rows,img2.rows);
    Mat imgUnion(rowsSum,colsSum,img1.type());
    Mat firstPart(imgUnion,Rect(0,0,img1.cols,img1.rows));
    img1.copyTo(firstPart);
    Mat secondPart(imgUnion,Rect(img1.cols,0,img2.cols,img2.rows));
    img2.copyTo(secondPart);
    return imgUnion;
}

int main(int argc, char* argv[])
{

    if (argc < 2) 
    {
        cout <<"Enter both paths" <<endl;
        return 1;
    }


    string path1 = argv[1];
    
    //the board is 6*7 with 11*11 cm
    int row = 6;
    int col = 7;
    int fieldSize = 11;
    Size size(row-1,col-1);
    //vector of Mat with the files in source path
    vector<Mat> files = createVecImgFromSource(path1);
    //vector with points to find the corners
    vector<vector<Point2f>> corners(files.size());
    //vector with the coordinates of the 3D points
    vector<vector<Point3f>> objectPoints;

    //size of an image
    int width;
    int height;

    vector<Point3f>objPoint;
    vector<Point2f> imgPoint;

    //Coordinates for 3D points
    for(int i=1;i<col;i++)
    {
        for(int j=1;j<row;j++)
        {
            objPoint.push_back(Point3f(j*fieldSize,i*fieldSize,0));
        }
    }

    //Detect feautures point/corners
    int i = 0;
    for(Mat &file : files)
    {
        bool found = findChessboardCorners(file,size,corners[i]);
        if(found == true)
        {
            objectPoints.push_back(objPoint);
        }
        width = file.cols;
        height = file.cols;

        drawChessboardCorners(file,size,corners[i],found);
        i++;
    }

    //intrinsic camera matrix
    Mat cameraMatrix;
    //distortion coefficient
    Vec<double,5> distCoeff(0,0,0,0,0);
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    vector<double> stdDeviationsIntrinsics, stdDeviationExtrensics, perViewErrors;
    Size imageSize(width,height);

    double meanReprojectionError = calibrateCamera(objectPoints,corners,imageSize,cameraMatrix,distCoeff,rvecs,tvecs);
    cout<<"Mean Reprojection error:"<<meanReprojectionError<<endl;
    
    //first output map for remap, second output map for remap,rectification transformation
    Mat map1, map2, R;
    initInverseRectificationMap(cameraMatrix,distCoeff,R,cameraMatrix,imageSize,CV_32FC1,map1,map2);
    
    string path2 = argv[2];
    Mat imgTest = imread(path2);
    Mat imgUndistorted;
    remap(imgTest,imgUndistorted,map1,map2,INTER_LINEAR);

    //to show the distorted and undistorted images in the same window, hconcat doesn't work because the 2 images have different size
    Mat imgUnion;
    if(imgTest.rows == imgUndistorted.rows && imgTest.cols==imgUndistorted.cols && imgTest.type()==imgUndistorted.type())
        hconcat(imgTest,imgUndistorted,imgUnion);
    else
        imgUnion = img1UnionImg2(imgTest,imgUndistorted);
    
    //only to display in my screen
    resize(imgUnion,imgUnion,Size(imgUnion.cols/4,imgUnion.rows/4));

    namedWindow("Distorted and undistorted images");
	imshow("Distorted and undistorted images", imgUnion);	
	waitKey(0);


    return 0;
}

