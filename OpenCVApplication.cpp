// OpenCVApplication.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "common.h"
#include "nlmeans.h"
#include <map>
#include <ctime>


int main(int argc, char *argv[])
{
    Mat src, dst1, dst2;

    //parse command line arguments
    char *source = argv[1];
    char *destinationPath = argv[2];
    int searchSize = 0, sampleSize = 0;
    float distanceSigma = 0, weightSigma = 0;

    /*if (argc > 3)
        searchSize = atoi(argv[3]);
    if (argc > 4)
        sampleSize = atoi(argv[4]);
    if (argc > 5)
        distanceSigma = atof(argv[5]);
    if (argc > 6)
        weightSigma = atof(argv[6]);*/
    searchSize = 11;
    sampleSize = 5;
    distanceSigma = 3;


    if (searchSize > 0)
        ip::SEARCH_SIZE = searchSize;
    if (sampleSize > 0)
        ip::SAMPLE_SIZE = sampleSize;
    if (distanceSigma > 0)
        ip::DISTANCE_SIGMA = distanceSigma;
    if (weightSigma > 0)
        ip::WEIGHT_SIGMA = weightSigma;

    src = imread(source, 0);
    
    clock_t start = clock();
    ip::Init();
    ip::DenoiseImage(src, dst1);
    clock_t end = clock();
    double elapsedSecs = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "My nlmeans: " << elapsedSecs << std::endl;
    ip::Clean();

    start = clock();
    fastNlMeansDenoising(src, dst2, 15, 5, 11);
    end = clock();
    elapsedSecs = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Their nlmeans: " << elapsedSecs << std::endl;

    /*vector<int> writeFlags;
    writeFlags.push_back(IMWRITE_PNG_COMPRESSION);
    writeFlags.push_back(IMWRITE_PNG_STRATEGY_DEFAULT);
    imwrite(destinationPath, dst, writeFlags);*/

    imshow("original", src);
    imshow("ours", dst1);
    imshow("theirs", dst2);
    
    waitKey(0);
	return 0;
}
