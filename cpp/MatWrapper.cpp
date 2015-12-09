//
//  MatWrapper.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "MatWrapper.h"


//width = cols, height = rows
MatWrapper::MatWrapper(int width, int height, InputArray data) {
    mat = new Mat(height, width, CV_64F);
    mat->setTo(data);
    
}

MatWrapper::MatWrapper(Mat * mat) {
    this->mat = mat;
}

MatWrapper::~MatWrapper() {
    delete mat;
}

// x is j, y is i
double MatWrapper::get(double x, double y) {
    return this->mat->at<double>(y, x);
}

// x is j, y is i
double MatWrapper::get(int x, int y) {
    return this->mat->at<double>(y, x);
}