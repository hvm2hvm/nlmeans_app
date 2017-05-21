#pragma once

#ifndef _NLMEANS_H_
#define _NLMEANS_H_

#include "common.h"

namespace ip {
    extern float **gauss;
    extern int SEARCH_SIZE;
    extern int SEARCH_EDGE;
    extern int SAMPLE_SIZE;
    extern int SAMPLE_EDGE;

    extern float DISTANCE_SIGMA;
    extern float GAUSS_SUM;

    extern float WEIGHT_SIGMA;

    void Init();
    void Clean();
    void PrintGauss();
    void DenoiseImage(Mat source, Mat& dest);
}

#endif