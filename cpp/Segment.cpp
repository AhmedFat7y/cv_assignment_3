//
//  Segment.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//


#include "Segment.h"

void Segment::linkPixel(PixelWrapper pixel) {
    pixels.push_back(pixel);
}

void Segment::addNeighbour(Segment segment) {
    neighbours.push_back(segment);
}

void Segment::updateMean() {
    this -> mean = 0;
    for (vector<PixelWrapper>::iterator itr = pixels.begin(); itr != pixels.end(); itr++) {
        this -> mean += itr->value;
    }
    if (pixels.size() > 0 ) {
        this -> mean /= pixels.size();
    }
}

void Segment::updateVariance() {
    this -> variance = 0;
    for (vector<PixelWrapper>::iterator itr = pixels.begin(); itr != pixels.end(); itr++) {
        this -> variance += itr->value;
    }
    if (pixels.size() > 0 ) {
        this -> variance /= pixels.size();
    }
}

void Segment::kill() {
    _isDead = true;
}

void Segment::survive() {
    _isDead = false;
}

bool Segment::isDead() {
    return _isDead;
}

bool Segment::isSurvivor() {
    return !_isDead;
}