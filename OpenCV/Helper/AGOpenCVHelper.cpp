//
//  AGOpenCVHelper.cpp
//  Mosaic Stitcher
//
//  Created by Aleksander Grzyb on 14/01/15.
//  Copyright (c) 2015 Aleksander Grzyb. All rights reserved.
//

#include "AGOpenCVHelper.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void AGOpenCVHelper::convertImageToColor(Mat &image)
{
    cvtColor(image, image, CV_GRAY2RGBA);
}

void AGOpenCVHelper::convertImageToGrayscale(cv::Mat &image)
{
    cvtColor(image, image, CV_RGBA2GRAY);
}

double AGOpenCVHelper::getDistanceBetweenPoints(const cv::Point &pointOne, const cv::Point &pointTwo)
{
    return sqrt(pow(pointOne.x - pointTwo.x, 2.0) + pow(pointOne.y - pointTwo.y, 2.0));
}

void AGOpenCVHelper::calculateLinearFunctionCoeffsUsingPoints(const cv::Point &pointOne, const cv::Point &pointTwo, std::vector<double> &coeffs)
{
    if (pointTwo.x == pointOne.x) {
        coeffs.push_back(0.00);
        coeffs.push_back(0.00);
        return;
    }
    double aCoeff = (double)(pointTwo.y - pointOne.y) / (double)(pointTwo.x - pointOne.x);
    double bCoeff = (double)(pointOne.y) - aCoeff * (double)(pointOne.x);
    coeffs.push_back(aCoeff);
    coeffs.push_back(bCoeff);
}

int AGOpenCVHelper::saveImage(const cv::Mat &image, const std::string &name, const std::string &savePath)
{
    string path = savePath + "/" + name + ".png";
    if (image.type() == CV_8UC4) {
        cvtColor(image, image, CV_BGRA2BGR);
    }
    if (!imwrite(path, image)) {
        cout << "Couldn't write image." << endl;
        return -1;
    }
    return 0;
}

void AGOpenCVHelper::createShiftMatrix(Mat &shiftMatrix, double dx, double dy)
{
    shiftMatrix = (Mat_<double>(2,3) << 1, 0, dx, 0, 1, dy);
}

bool AGOpenCVHelper::isPixelWhiteInImage(const cv::Mat &image, const cv::Point pixelPosition)
{
    if (pixelPosition.x >= 0 && pixelPosition.x < image.cols && pixelPosition.y >= 0 && pixelPosition.y < image.rows) {
        uchar pixelValue = image.at<uchar>(pixelPosition.y, pixelPosition.x);
        if (pixelValue == WHITE_PIXEL) {
            return true;
        }
        return false;
    }
    return false;
}

void AGOpenCVHelper::showImage(const cv::Mat &image, const std::string &windowName)
{
    imshow(windowName.c_str(), image);
    waitKey();
}

void AGOpenCVHelper::rotateImage(Mat &image, double angle)
{
    int len = max(image.cols, image.rows);
    Point2f pt(len * 0.5, len * 0.5);
    Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(image, image, r, Size(len, len));
}


string AGOpenCVHelper::getImageTypeNameUsingImageType(int imageType)
{
    int numberOfImageTypes = 35;
    int enumInts[] = {CV_8U,  CV_8UC1,  CV_8UC2,  CV_8UC3,  CV_8UC4,
        CV_8S,  CV_8SC1,  CV_8SC2,  CV_8SC3,  CV_8SC4,
        CV_16U, CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4,
        CV_16S, CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4,
        CV_32S, CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4,
        CV_32F, CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4,
        CV_64F, CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4};
    
    string enumStrings[] = {"CV_8U",  "CV_8UC1",  "CV_8UC2",  "CV_8UC3",  "CV_8UC4",
        "CV_8S",  "CV_8SC1",  "CV_8SC2",  "CV_8SC3",  "CV_8SC4",
        "CV_16U", "CV_16UC1", "CV_16UC2", "CV_16UC3", "CV_16UC4",
        "CV_16S", "CV_16SC1", "CV_16SC2", "CV_16SC3", "CV_16SC4",
        "CV_32S", "CV_32SC1", "CV_32SC2", "CV_32SC3", "CV_32SC4",
        "CV_32F", "CV_32FC1", "CV_32FC2", "CV_32FC3", "CV_32FC4",
        "CV_64F", "CV_64FC1", "CV_64FC2", "CV_64FC3", "CV_64FC4"};
    
    for(int i = 0; i < numberOfImageTypes; i++) {
        if(imageType == enumInts[i]) return enumStrings[i];
    }
    return "Unknown image type.";
}

int AGOpenCVHelper::loadImage(cv::Mat &image, const std::string &loadPath)
{
    image = imread(loadPath, CV_LOAD_IMAGE_COLOR);
    if(!image.data) {
        cout <<  "Couldn't open or find the image." << endl;
        return -1;
    }
    return 0;
}


