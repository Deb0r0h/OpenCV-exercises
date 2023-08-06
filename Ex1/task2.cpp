#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "task2.h"


using namespace std;
using namespace cv;


void max(Mat image,Mat final_image,int kernel_size)
{
    
    int rows = image.rows;
	int colums = image.cols;

	int posMaxi = 0;
	int posMaxj = 0;
	int center = kernel_size/2;

	double minVal; 
	double maxVal; 
	Point minLoc; 
	Point maxLoc;
	minMaxLoc(final_image, &minVal, &maxVal, &minLoc, &maxLoc );

	for(int initial_row=0;initial_row<rows-kernel_size+1;initial_row++)
	{
		for(int initial_colum=0;initial_colum<colums-kernel_size+1;initial_colum++)
		{
			//int max = 0;
			int max = (int)minVal-1;
			for(int i=0;i<kernel_size;i++)
			{
				for(int j=0;j<kernel_size;j++)
				{
					if(image.at<unsigned char>(initial_row+i,initial_colum+j)>max)
					{
						max = image.at<unsigned char>(initial_row+i,initial_colum+j);
						posMaxi = initial_row+i;
						posMaxj = initial_colum+j;
					}
				}
			}
			final_image.at<unsigned char>(initial_row+center,initial_colum+center) = image.at<unsigned char>(posMaxi,posMaxj);
		}
	}
}

void min(Mat image,Mat final_image,int kernel_size)
{
    int rows = image.rows;
	int colums = image.cols;

	int posMini = 0;
	int posMinj = 0;
	int center = kernel_size/2;
	
	double minVal; 
	double maxVal; 
	Point minLoc; 
	Point maxLoc;
	minMaxLoc(final_image, &minVal, &maxVal, &minLoc, &maxLoc );

	

	for(int initial_row=0;initial_row<rows-kernel_size+1;initial_row++)
	{
		for(int initial_colum=0;initial_colum<colums-kernel_size+1;initial_colum++)
		{
			//unsigned char //int min = image.at<unsigned char>(0,0);
			int min = (int)maxVal+1;
			for(int i=0;i<kernel_size;i++)
			{
				for(int j=0;j<kernel_size;j++)
				{
					if(image.at<unsigned char>(initial_row+i,initial_colum+j)<min)
					{
						min = image.at<unsigned char>(initial_row+i,initial_colum+j);
						posMini = initial_row+i;
						posMinj = initial_colum+j;
					}
				}
			}
			final_image.at<unsigned char>(initial_row+center,initial_colum+center) = image.at<unsigned char>(posMini,posMinj);
		}
	}
}




int main(int argc, char** argv)
{
    Mat img = imread(argv[1]);
	if(img.empty())
	{
		cout<<"Provide a valid image\n";
		return -1;
	}
	

    //convert to gray scale
	Mat img_gray, final_imageMIN, final_imageMAX;
	cvtColor(img,img_gray,COLOR_RGB2GRAY);
	cvtColor(img,final_imageMIN,COLOR_RGB2GRAY);
	cvtColor(img,final_imageMAX,COLOR_RGB2GRAY);


	

    max(img_gray,final_imageMAX,7);
	min(img_gray,final_imageMIN,5);


	


	//namedWindow("Initial image");
	//imshow("Initial image", img_gray);
	//imwrite("Initial image.jpg", img_gray);

	resize(final_imageMIN,final_imageMIN,Size(img.cols/4.0,img.rows/4.0));
	namedWindow("Modified image MIN");
	imshow("Modified image MIN", final_imageMIN);
	//imwrite("kernel7MIN.jpg", final_imageMIN);
	
	//namedWindow("Modified image MAX");
	//imshow("Modified image MAX", final_imageMAX);
	//imwrite("kernel7MAX.jpg", final_imageMAX);
	
    waitKey(0);	
	return 0;

}
