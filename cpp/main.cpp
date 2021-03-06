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
double threshold = 30;
int main(int argc, const char * argv[]) {
//    vector<PixelWrapper> points = {
//        PixelWrapper(1,7, 1),
//        PixelWrapper(2,6, 1),
//        PixelWrapper(3,5, 1),
//        PixelWrapper(4,4, 1),
//        PixelWrapper(5,3, 1),
//        PixelWrapper(6,2, 1),
//        PixelWrapper(7,1, 1)
//    };
//    for(vector<PixelWrapper>::iterator itr = points.begin(); itr != points.end(); itr++) {
//        PixelWrapper & pix = *itr;
//        pix.x = 34;
//    }
//    cout << points << endl << endl;
    uchar test_data[4 * 4] = {
        77, 69, 100, 54,
        66, 4, 98, 19,
        3, 74, 38, 58,
        50, 62, 65, 78
    };
//    Mat img = Mat(4, 4, CV_8U, test_data);
    Mat img = imread(path + "house.bmp", CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
    AdaptivePyramidAlgorithm algorithm(img, threshold);
    algorithm.init();
    algorithm.start();
    algorithm.applyResult();
    imshow("Modified Image", img);
    waitKey();
    return 0;
}
