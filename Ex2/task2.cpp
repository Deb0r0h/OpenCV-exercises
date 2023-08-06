#include <iostream>
#include <opencv2/opencv.hpp>


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
        cout<<"BGR["<<(int)image_out.at<Vec3b>(y,x)[0]<<" "<<(int)image_out.at<Vec3b>(y,x)[1]<<" "<<(int)image_out.at<Vec3b>(y,x)[1]<<"]"<<endl;
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