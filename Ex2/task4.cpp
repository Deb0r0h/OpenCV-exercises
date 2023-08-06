#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

#define NEIGHBORHOOD_X 9
#define NEIGHBORHOOD_Y 9


void onMouse(int event,int x,int y,int f, void* userdata)
{
    if(event == EVENT_LBUTTONDOWN)
    {
        Mat image = *(Mat*)userdata; 
        Mat image_out = image.clone();
    
        if(y+NEIGHBORHOOD_Y>image_out.rows || x+NEIGHBORHOOD_X>image_out.cols)
            return;
        
        cv::Rect rect(x,y,NEIGHBORHOOD_X,NEIGHBORHOOD_Y);

        int val = 0;
        Mat img = image_out(rect);
        vector<int> mediaR; 
        vector<int> mediaG;
        vector<int> mediaB;
        
        for(int i=0;i<img.rows;i++)
        {
            for(int j=0;j<img.cols;j++)
            {
                val = (int)img.at<Vec3b>(i,j)[0];
                mediaB.push_back(val);
                val = (int)img.at<Vec3b>(i,j)[1];
                mediaG.push_back(val);
                val = (int)img.at<Vec3b>(i,j)[2];
                mediaR.push_back(val);
            }
        }
        double meanR;
        double meanG;
        double meanB;
        int sommaR = 0;
        int sommaG = 0;
        int sommaB = 0;
        double size = (double)mediaR.size();
        for(int i =0;i<size;i++)
        {
            sommaB = sommaB +mediaB[i];
            sommaG = sommaG +mediaG[i];
            sommaR = sommaR +mediaR[i];
        }
        meanB = sommaB/size;
        meanG = sommaG/size;
        meanR = sommaR/size;
       
        Mat mask(image_out.rows, image_out.cols, CV_8UC1);
        int b = (int)meanB;
        int g = (int)meanG;
        int r = (int)meanR;

        int T = 75;

        for(int i =0;i<image_out.rows;i++)
        {
            for(int j=0;j<image_out.cols;j++)
            {
                if(fabs(image_out.at<Vec3b>(i,j)[0]-b)<T && fabs(image_out.at<Vec3b>(i,j)[1]-g)<T && fabs(image_out.at<Vec3b>(i,j)[2]-r)<T)
                    mask.at<unsigned char>(i,j) = 255;
                else
                    mask.at<unsigned char>(i,j) = 0;
            }
        }

		namedWindow("Mask");
		imshow("Mask", mask);
        //imwrite("mashera.jpg",mask);
    }
}


int main()
{
		Mat img = imread("robocup.jpg");
		if(img.empty())
		{
			cout<<"Provide a valid image\n";
			return -1;
		}
		
        resize(img,img,Size(img.cols/2.0,img.rows/2.0));
		
		namedWindow("Image");
		imshow("Image", img);

        setMouseCallback("Image", onMouse,(void*)&img);
		
		waitKey(0);
		return 0;
}