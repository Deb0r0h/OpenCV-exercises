#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
    Mat img = imread(argv[1]);
	if(img.empty())
	{
		cout<<"Provide a valid image\n";
		return -1;
	}
		
	Mat img_gray;
	cvtColor(img,img_gray,COLOR_RGB2GRAY);



	namedWindow("Image 1");
	imshow("Image 1", img_gray);
		
	waitKey(0);
		
		
	return 0;

}