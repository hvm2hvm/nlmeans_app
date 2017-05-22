// OpenCVApplication.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "common.h"
#include "nlmeans.h"
#include <map>



int main(int argc, char *argv[])
{
    Mat src, dst;

    //parse command line arguments
    char *source = argv[1];
    char *destinationPath = argv[2];
    int searchSize = 0, sampleSize = 0;
    float distanceSigma = 0, weightSigma = 0;

    if (argc > 3)
        searchSize = atoi(argv[3]);
    if (argc > 4)
        sampleSize = atoi(argv[4]);
    if (argc > 5)
        distanceSigma = atof(argv[5]);
    if (argc > 6)
        weightSigma = atof(argv[6]);

    if (searchSize > 0)
        ip::SEARCH_SIZE = searchSize;
    if (sampleSize > 0)
        ip::SAMPLE_SIZE = sampleSize;
    if (distanceSigma > 0)
        ip::DISTANCE_SIGMA = distanceSigma;
    if (weightSigma > 0)
        ip::WEIGHT_SIGMA = weightSigma;

    src = imread(source, 0);

    ip::Init();
    ip::DenoiseImage(src, dst);
    ip::Clean();

    vector<int> writeFlags;
    writeFlags.push_back(IMWRITE_PNG_COMPRESSION);
    writeFlags.push_back(IMWRITE_PNG_STRATEGY_DEFAULT);
    imwrite(destinationPath, dst, writeFlags);

    /*imshow("original", src);
    imshow("denoised", dst);
    
    waitKey(0);*/
	return 0;
}
