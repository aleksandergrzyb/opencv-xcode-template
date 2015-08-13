//
//  AGOpenCVHelper.h
//  Mosaic Stitcher
//
//  Created by Aleksander Grzyb on 14/01/15.
//  Copyright (c) 2015 Aleksander Grzyb. All rights reserved.
//

#ifndef __Mosaic_Stitcher__AGOpenCVHelper__
#define __Mosaic_Stitcher__AGOpenCVHelper__

#include <stdio.h>
#include <opencv2/core/core.hpp>

#define A_COEFF 0
#define B_COEFF 1

const int WHITE_PIXEL = 0xFF;

class AGOpenCVHelper {
public:
    // Handling image types
    static void convertImageToColor(cv::Mat &image);
    static void convertImageToGrayscale(cv::Mat &image);
    static std::string getImageTypeNameUsingImageType(int imageType);
    
    // Geometric methods
    static void calculateLinearFunctionCoeffsUsingPoints(const cv::Point &pointOne, const cv::Point &pointTwo, std::vector<double> &coeffs);
    static double getDistanceBetweenPoints(const cv::Point &pointOne, const cv::Point &pointTwo);
    
    // Image data introspection
    static bool isPixelWhiteInImage(const cv::Mat &image, const cv::Point pixelPosition);
    
    // Image transformations
    static void createShiftMatrix(cv::Mat &shiftMatrix, double dx, double dy);
    static void rotateImage(cv::Mat &image, double angle);
    static void flipImage(cv::Mat &image);
    
    // Saving and showing
    static int saveImage(const cv::Mat &image, const std::string &name, const std::string &savePath);
    static void showImage(const cv::Mat &image, const std::string &windowName);
    static int loadImage(cv::Mat &image, const std::string &loadPath);
};

#endif /* defined(__Mosaic_Stitcher__AGOpenCVHelper__) */
