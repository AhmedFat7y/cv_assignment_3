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

void Segment::addNeighbours(vector<Segment> neighbours){
    this->neighbours.insert(this->neighbours.end(), neighbours.begin(), neighbours.end());
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
        this -> variance += pow(itr->value - this->mean, 2);
    }
    if (pixels.size() > 0 ) {
        this -> variance /= pixels.size();
    }
}

void Segment::SurviveOrKill() {
    for(vector<Segment>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if(!itr->isMarked() && itr->mean < this->mean) {
            kill();
        }
    }
    survive();
    for(vector<Segment>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if(!itr->isMarked()) {
            itr->kill();
        }
    }
}

void Segment::kill() {
    _isDead = true;
    _isMarked = true;
}

void Segment::survive() {
    _isDead = false;
    _isMarked = true;
}

bool Segment::isDead() {
    return _isDead;
}

bool Segment::isMarked() {
    return _isMarked;
}
bool Segment::isSurvivor() {
    return !_isDead;
}
