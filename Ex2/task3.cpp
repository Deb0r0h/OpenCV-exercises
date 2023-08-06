#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

#define NEIGHBORHOOD_X 9
#define NEIGHBORHOOD_Y 9

void meanBGR(cv::Rect rect, Mat image_out)
{
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

        cout<<"avgB:"<<meanB<<" "<<"avgG:"<<meanG<<" "<<"avgR:"<<meanR<<endl;
}


void onMouse(int event,int x,int y,int f, void* userdata)
{
    if(event == EVENT_LBUTTONDOWN)
    {
        Mat image = *(Mat*)userdata; 
        Mat image_out = image.clone();
    
        if(y+NEIGHBORHOOD_Y>image_out.rows || x+NEIGHBORHOOD_X>image_out.cols)
            return;
        
        cv::Rect rect(x,y,NEIGHBORHOOD_X,NEIGHBORHOOD_Y);

        meanBGR(rect, image_out);
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