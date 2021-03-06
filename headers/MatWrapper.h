//
//  MatWrapper.h
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef assignment_3_MatWrapper_h
#define assignment_3_MatWrapper_h

#define ELEMENT_TYPE uchar

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


class MatWrapper {
public:
    Mat * mat;
    int width; // cols
    int height; // row
    MatWrapper();
    MatWrapper(int cols, int rows, InputArray data);
    MatWrapper(Mat & mat);
    // x is j, y is i
    ELEMENT_TYPE get(double x, double y);
    // x is j, y is i
    ELEMENT_TYPE get(int x, int y);
    void set(int x, int y, ELEMENT_TYPE value);
    vector<Point2i> getNeighbours (int x, int y);
    vector<ELEMENT_TYPE> getNeighboursValues (int x, int y);
    double calculateVariance(int x, int y);
    ~MatWrapper();
};

#endif
