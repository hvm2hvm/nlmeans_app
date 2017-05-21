// OpenCVApplication.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "common.h"
#include "nlmeans.h"
#include <map>



int main()
{
    Mat src, dst;
    src = imread("Images\\gauss1.bmp", 0);

    ip::Init();
    ip::DenoiseImage(src, dst);
    ip::Clean();

    imshow("original", src);
    imshow("denoised", dst);
    
    waitKey(0);
	return 0;
}