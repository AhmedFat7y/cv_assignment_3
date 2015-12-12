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

void Segment::addPixels(vector<PixelWrapper> pixels) {
    pixels.insert(pixels.end(), pixels.begin(), pixels.end());
}

void Segment::addPixel(PixelWrapper const &pixel) {
    pixels.push_back(pixel);
}

void Segment::addNeighbour(Segment &segment) {
    neighbours.insert(neighbours.end(), &segment);
}

void Segment::removeNeighbour(Segment *segment) {
    vector<Segment*>::iterator itr = neighbours.begin();
    while (itr != neighbours.end()) {
        if(*itr == segment) {
            itr = neighbours.erase(itr);
        } else {
            itr ++;
        }
    }
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
        double absoluteDifference = abs((*itr)->mean - this->mean);
        if( absoluteDifference < minAbsoluteDiff) {
            minAbsoluteDiff = minAbsoluteDiff;
            minItr = itr;
        }
    }
    return (*minItr);
}

// TODO revisit this one
//merge segment with best survivor and remove its pointers from the neighbours
void Segment::mergeSegment() {
    if(!isMarked()) {
        throw Exception();
    }
    Segment * masterNodeItr = getBestSurvivor();
    masterNodeItr->addPixels(pixels);
    for (vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        (*itr)->removeNeighbour(this);
    };
    // merge neighbours too plz!
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

void Segment::resetFlags() {
    _isMarked = false;
    _isDead = false;
}

