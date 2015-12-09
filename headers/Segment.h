//
//  Segment.h
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef __assignment_3__Segment__
#define __assignment_3__Segment__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "PixelWrapper.h"

using namespace cv;
using namespace std;


class Segment {
public:
    bool _isDead;
    double mean;
    double variance;
    vector<PixelWrapper> pixels;
    vector<Segment> neighbours;
    void linkPixel(PixelWrapper pixel);
    void addNeighbour(Segment segment);
    void updateMean();
    void updateVariance();
    void kill();
    void survive();
    bool isSurvivor();
    bool isDead();
//    void addNeighbours(vector<Point2i> &neighbours, int width);
};

#endif /* defined(__assignment_3__Segment__) */
