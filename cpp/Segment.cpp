//
//  Segment.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//


#include "Segment.h"

Segment::Segment() :_isDead(false), _isMarked(false){
}

void Segment::linkSegment(Segment &segmentToBeMerged) {
    pixels.insert(pixels.end(), segmentToBeMerged.pixels.begin(), segmentToBeMerged.pixels.end());
}
void Segment::addPixel(PixelWrapper const &pixel) {
    pixels.push_back(pixel);
}

void Segment::addNeighbour(Segment &segment) {
    neighbours.insert(neighbours.end(), &segment);
}

void Segment::addNeighbours(vector<Segment*> &neighbours){
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
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if(!(*itr)->isMarked() && (*itr)->variance < this->variance) {
            return ;
        }
    }
    survive();
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if(!(*itr)->isMarked()) {
            (*itr)->kill();
        }
    }
}

Segment * Segment::getBestSurvivor() {
    double minAbsoluteDiff = (255 * 255) + 1; // to make sure it's bigger than max pixel intensity squared
    vector<Segment*>::iterator minItr;
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        double absoluteDifference = pow((*itr)->mean - this->mean, 2);
        if( absoluteDifference < minAbsoluteDiff) {
            minAbsoluteDiff = minAbsoluteDiff;
            minItr = itr;
        }
    }

    return (*minItr);

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
