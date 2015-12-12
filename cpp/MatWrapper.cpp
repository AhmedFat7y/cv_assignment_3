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
    this->width = cols;
    this->height = rows;
    this->mat = new Mat(height, width, CV_8U);
    this->mat->setTo(data);
}

MatWrapper::MatWrapper(Mat & mat) {
    this->mat = &mat;
    this->width = mat.cols;
    this->height = mat.rows;
}

MatWrapper::~MatWrapper() {
    delete mat;
}

// x is j, y is i
ELEMENT_TYPE MatWrapper::get(double x, double y) {
    return this->mat->at<ELEMENT_TYPE>(y, x);
}

// x is j, y is i
ELEMENT_TYPE MatWrapper::get(int x, int y) {
    return this->mat->at<ELEMENT_TYPE>(y, x);
}

vector<Point2i> MatWrapper::getNeighbours (int x, int y) {
    vector<Point2i> neighbourPoints = {
        Point2i(x - 1, y - 1),
        Point2i(x, y - 1),
        Point2i(x + 1, y - 1),
        Point2i(x - 1, y),
//        Point2i(x, y), No need apparently!
        Point2i(x + 1, y),
        Point2i(x - 1, y + 1),
        Point2i(x , y + 1),
        Point2i(x + 1, y + 1),
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


vector<ELEMENT_TYPE> MatWrapper::getNeighboursValues (int x, int y) {
    vector<ELEMENT_TYPE> neighboursValues;
    vector<Point2i> neighbourPoints = {
        Point2i(x - 1, y - 1),
        Point2i(x, y - 1),
        Point2i(x + 1, y - 1),
        Point2i(x - 1, y),
        Point2i(x, y),
        Point2i(x + 1, y),
        Point2i(x - 1, y + 1),
        Point2i(x , y + 1),
        Point2i(x + 1, y + 1),
    };
    for(vector<Point2i>::iterator itr = neighbourPoints.begin(); itr != neighbourPoints.end(); itr++) {
        if (itr->x >= width || itr->x < 0 || itr->y < 0 || itr->y >= height) {
            continue;
        }
        neighboursValues.push_back(get(itr->x, itr->y));
    }
    return neighboursValues;
}

double MatWrapper::calculateVariance(int x, int y) {
    double variance = 0;
    double mean = 0;
    double temp = 0;
    vector<ELEMENT_TYPE> neighbourPixels = getNeighboursValues(x, y);
    // calculate mean
    for (vector<ELEMENT_TYPE>::iterator itr = neighbourPixels.begin(); itr != neighbourPixels.end(); itr++) {
        temp = *itr;
        mean += *itr;
    }
    if (neighbourPixels.size() > 0) {
        mean /= neighbourPixels.size();
    }

    //calculate the variance
    for (vector<ELEMENT_TYPE>::iterator itr = neighbourPixels.begin(); itr != neighbourPixels.end(); itr++) {
        temp = *itr;
        variance += pow(mean - (double)*itr, 2);
    }
    if (neighbourPixels.size() > 0) {
        variance /= neighbourPixels.size();
    }

    return variance;
}
