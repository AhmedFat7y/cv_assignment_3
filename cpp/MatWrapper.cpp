//
//  MatWrapper.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "MatWrapper.h"

MatWrapper::MatWrapper() {
    mat = new Mat();
}

//width = cols, height = rows
MatWrapper::MatWrapper(int cols, int rows, InputArray data) {
    this->mat = new Mat(height, width, CV_64F);
    this->width = cols;
    this->height = rows;
    this->mat->setTo(data);
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

vector<Point2i> MatWrapper::getNeibours (int x, int y) {
    vector<Point2i> neighbourPoints = {
        Point2d(x - 1, y - 1),
        Point2d(x, y - 1),
        Point2d(x + 1, y - 1),
        Point2d(x - 1, y),
        Point2d(x, y),
        Point2d(x + 1, y),
        Point2d(x - 1, y + 1),
        Point2d(x , y + 1),
        Point2d(x + 1, y + 1),
    };
    vector<Point2i>::iterator it = neighbourPoints.begin();
    while(it != neighbourPoints.end()) {
        if (it->x >= width || it->x < 0 || it->y < 0 || it->y >= height) {
            it = neighbourPoints.erase(it);
        } else {
            ++it;
        }
    }
    return neighbourPoints;
}
