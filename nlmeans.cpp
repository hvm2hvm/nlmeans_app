#include "nlmeans.h"

namespace ip {

    float **gauss;
    int SEARCH_SIZE = 21;
    int SEARCH_EDGE = SEARCH_SIZE / 2;
    int SAMPLE_SIZE = 7;
    int SAMPLE_EDGE = SAMPLE_SIZE / 2;

    float DISTANCE_SIGMA = 3.0f;
    float GAUSS_SUM = 0;

    float WEIGHT_SIGMA = 255.0f;

    void Init();
    void Clean();

    void AllocateGauss() {
        gauss = new float*[SAMPLE_SIZE];
        for (int i = 0; i < SAMPLE_SIZE; i++)
            gauss[i] = new float[SAMPLE_SIZE];
    }

    float ComputeGaussPoint(int di, int dj) {
        float expPower = -(float)(di * di + dj * dj) / (float)(2 * DISTANCE_SIGMA * DISTANCE_SIGMA);
        float value = 1.0f / 2.0f / PI / DISTANCE_SIGMA / DISTANCE_SIGMA * exp(expPower);
        return value;
    }

    void ComputeGauss() {
        AllocateGauss();
        
        for (int i = 0; i < SAMPLE_SIZE; i++) {
            for (int j = 0; j < SAMPLE_SIZE; j++) {
                int di = i - SAMPLE_EDGE;
                int dj = j - SAMPLE_EDGE;

                gauss[i][j] = ComputeGaussPoint(di, dj);
                GAUSS_SUM += gauss[i][j];
            }
        }
    } 

    void PrintGauss() {
        for (int i = 0; i < SAMPLE_SIZE; i++) {
            for (int j = 0; j < SAMPLE_SIZE; j++)
                std::cout << gauss[i][j] << " ";
            std::cout << std::endl;
        }
    }
    
    void Init() {
        ComputeGauss();
    }

    void Clean() {        
        for (int i = 0; i < SAMPLE_SIZE; i++)
            delete[] gauss[i];
        delete[] gauss;
    }

    int BoundPixel(int pixel) {
        if (pixel < 0)
            return 0;
        else if (pixel > 255)
            return 255;
        else
            return pixel;
    }

    float GetWeight(Mat source, Point2i p1, Point2i p2) {
        float sumOfWeightedDiffs = 0.0f;

        for (int dx = -SAMPLE_EDGE; dx <= SAMPLE_EDGE; dx++) {
            for (int dy = -SAMPLE_EDGE; dy <= SAMPLE_EDGE; dy++) {
                int x1 = p1.x + dx;
                int y1 = p1.y + dy;
                int x2 = p2.x + dx;
                int y2 = p2.y + dy;

                int pixelDifference = (int)source.at<uchar>(y1, x1) - (int)source.at<uchar>(y2, x2);
                float weightedDiff = gauss[dx + SAMPLE_EDGE][dy + SAMPLE_EDGE] * pixelDifference * pixelDifference;
                sumOfWeightedDiffs += weightedDiff;
            }
        }

        float pixelWeight = exp(-sumOfWeightedDiffs / WEIGHT_SIGMA / GAUSS_SUM);
        return pixelWeight;
    }

    

    int DenoisePixel(Mat source, Point2i p1) {
        float weightedSum = 0.0f;
        float sumOfWeights = 0.0f;

        for (int dx = -SEARCH_EDGE; dx <= SEARCH_EDGE; dx++) {
            for (int dy = -SEARCH_EDGE; dy <= SEARCH_EDGE; dy++) {
                int xx = p1.x + dx;
                int yy = p1.y + dy;

                float weight = GetWeight(source, p1, Point2i(xx, yy));
                weightedSum += weight * (int)source.at<uchar>(yy, xx);
                sumOfWeights += weight;
            }
        }

        int pixelNewValue = weightedSum / sumOfWeights;
        return BoundPixel(pixelNewValue);
    }

    void DenoiseImage(Mat source, Mat& dest) {
        int offset = SEARCH_EDGE + SAMPLE_EDGE + 1;

        dest = source.clone();

        for (int x = offset; x <= source.cols - offset; x++)
            for (int y = offset; y <= source.rows - offset; y++)
                dest.at<uchar>(y, x) = DenoisePixel(source, Point2i(x, y));
    }
    
}
