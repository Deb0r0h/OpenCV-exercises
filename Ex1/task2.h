#include <opencv2/highgui.hpp>

#ifndef helper_functions_h
#define helper_functions_h

void min(cv::Mat image,cv::Mat final_image,int kernel_size);
void max(cv::Mat image,cv::Mat final_image,int kernel_size);

#endif