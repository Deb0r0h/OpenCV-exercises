#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

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
        
		waitKey(0);
		return 0;
}
