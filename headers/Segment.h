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
    bool _isMarked;
    double mean;
    double variance;
    vector<PixelWrapper> pixels;
    vector<Segment*> neighbours;
    Segment * masterSegment;
    Segment();
    void addPixel(PixelWrapper const &pixel);
    void addPixels(vector<PixelWrapper> &pixels);
    void addNeighbour(Segment &segment);
    void addNeighbour(Segment *segment);
    void addNeighbours(vector<Segment*> &neighbours);
    void removeNeighbour(Segment * segment);
    void updateMean();
    void updateVariance();
    void SurviveOrKill();
    void prepareForRemoval();
    void kill();
    Segment * getBestSurvivor();
    void spreadMasterSegment();
    void survive();
    bool isSurvivor();
    bool isDead();
    bool isMarked();
    void linkSegment();
    void resetFlags();
};

#endif /* defined(__assignment_3__Segment__) */
