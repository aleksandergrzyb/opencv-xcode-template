//
//  AGDataStructures.h
//  Mosaic Stitcher
//
//  Created by Aleksander Grzyb on 06/02/15.
//  Copyright (c) 2015 Aleksander Grzyb. All rights reserved.
//

#ifndef Mosaic_Stitcher_AGDataStructures_h
#define Mosaic_Stitcher_AGDataStructures_h

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <opencv2/stitching/stitcher.hpp>
#include <vector>

// Preprocessing
const int WHITE_PIXEL = 0xFF;
const int FIRST_ROW = 0;

// Mosaic Stitcher
const double PATH_X_OFFSET = 0.1;
const double PATH_Y_OFFSET = 0.1;

// Path Finding
const double POINT_Y_OFFSET = 0.1;
const double POINT_X_OFFSET = 0.1;

// Informs about relationship between two images. For example direction 'Up' tells that first image is below second image and the first image would be transformed.
enum ImageDirection {
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3
};

struct AGError {
    bool isError;
    std::string description;
};

struct AGParameters {
    bool clustering;
    bool isAdHoc;
    bool simplerTransform;
    bool rigidTransform;
    bool usePaths;
    double angleParameter;
    double lengthParameter;
    double percentOverlap;
    double shiftParameter;
    std::string mosaicSaveAbsolutePath;
    std::string imagesDirectoryAbsolutePath;
};

struct AGImage {
    AGImage(cv::Mat image, int xCoordinate, int yCoordinate, int width, int height, std::string name) : image(image), xCoordinate(xCoordinate), yCoordinate(yCoordinate), width(width), height(height), name(name) {}
    cv::Mat image;
    cv::Mat mask;
    cv::Mat distanceTransform;
    // Using width and height, because when creating final grid the image is copyied to that grid and loses information about its original width and height, which is needed for matches filtering
    int width;
    int height;
    int xCoordinate;
    std::string name;
    int yCoordinate;
    std::vector<cv::KeyPoint> keypoints;
    std::vector<cv::Point> pathPoints;
};

#endif
