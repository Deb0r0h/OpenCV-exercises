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

    Mat hist;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    
    calcHist(&img_gray, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
             Scalar(255, 255, 255), 2, LINE_AA);
    }

    
    Mat equalized;
    equalizeHist(img_gray, equalized);

    
    Mat eqHist;
    calcHist(&equalized, 1, 0, Mat(), eqHist, 1, &histSize, &histRange, uniform, accumulate);

    
    Mat eqHistImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    normalize(eqHist, eqHist, 0, eqHistImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(eqHistImage, Point(bin_w * (i - 1), hist_h - cvRound(eqHist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(eqHist.at<float>(i))),
             Scalar(255, 255, 255), 2, LINE_AA);
    }

    
    
	namedWindow("Histogram with equalization");
	imshow("Histogram with equalization", eqHistImage);
    imwrite("histoE.jpg", eqHistImage);
			
	waitKey(0);
	return 0;
}