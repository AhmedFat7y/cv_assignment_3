//
//  main.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#include "AdaptivePyramidAlgorithm.h"

string path = "/Users/MacBookAir/Documents/guc-projects/cv/assignment-3/";

int main(int argc, const char * argv[]) {
    Mat img = imread(path + "house.bmp", CV_LOAD_IMAGE_COLOR);   // Read the file
    AdaptivePyramidAlgorithm algorithm(img);
    algorithm.init();
    return 0;
}
