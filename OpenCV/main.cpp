//
//  main.cpp
//  OpenCV
//
//  Created by Aleksander Grzyb on 12/08/15.
//  Copyright (c) 2015 Aleksander Grzyb. All rights reserved.
//

#include <iostream>
#include "AGOpenCVHelper.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// images path
static const std::string imagesPath = "/Users/aleksandergrzyb/Desktop/images/";

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    Mat image;
    if (AGOpenCVHelper::loadImage(image, imagesPath + "image1.tif") != -1) {
        AGOpenCVHelper::showImage(image, "image1");
    }
}
