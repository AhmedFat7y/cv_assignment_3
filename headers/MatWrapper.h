//
//  MatWrapper.h
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef assignment_3_MatWrapper_h
#define assignment_3_MatWrapper_h

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


class MatWrapper {
    Mat * mat;
    MatWrapper(int width, int height, InputArray data);
    MatWrapper(Mat * mat);
    double get(double x, double y);
    double get(int x, int y);
    ~MatWrapper();
};

#endif
