//
//  Segment.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//


#include "Segment.h"

void removeFromList(vector<Segment*> & segments, Segment * toBeRemoved) {
    vector<Segment*>::iterator itr = segments.begin();
    while (itr != segments.end()) {
        if(*itr == toBeRemoved) {
            itr = segments.erase(itr);
        } else {
            itr ++;
        }
    }
}

Segment::Segment() :_isDead(false), _isMarked(false), masterSegment(0){
}

void Segment::addPixels(vector<PixelWrapper> &newPixels) {
    pixels.insert(pixels.end(), newPixels.begin(), newPixels.end());
}

void Segment::addPixel(PixelWrapper const &pixel) {
    pixels.push_back(pixel);
}

void Segment::addNeighbour(Segment &segment) {
    neighbours.insert(neighbours.end(), &segment);
}

void Segment::addNeighbour(Segment *segment) {
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if((*itr) == segment) {
            return ;
        }
    }
    neighbours.insert(neighbours.end(), segment);
}

void Segment::removeNeighbour(Segment *segment) {
    removeFromList(neighbours, segment);
}

void Segment::addNeighbours(vector<Segment*> &newNeighbours){
    neighbours.insert(neighbours.end(), newNeighbours.begin(), newNeighbours.end());
}

void Segment::updateMean() {
    this -> mean = 0;
    for (vector<PixelWrapper>::iterator itr = pixels.begin(); itr != pixels.end(); itr++) {
        this->mean += itr->value;
    }
    if (pixels.size() > 0 ) {
        this->mean /= pixels.size();
    }
}

void Segment::updateVariance() {
    this -> variance = 0;
    for (vector<PixelWrapper>::iterator itr = pixels.begin(); itr != pixels.end(); itr++) {
        this->variance += pow(itr->value - this->mean, 2);
    }
    if (pixels.size() > 0 ) {
        this->variance /= pixels.size();
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
void Segment::spreadMasterSegment() {
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if(*itr != masterSegment) {
            (*itr)->addNeighbour(masterSegment);
        }
    }
}

Segment * Segment::getBestSurvivor() {
    double minAbsoluteDiff = (255 * 255) + 1; // to make sure it's bigger than max pixel intensity squared
    vector<Segment*>::iterator minItr;
    for(vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
        if((*itr)->isSurvivor()) {
            double absoluteDifference = abs((*itr)->mean - this->mean);
            if (absoluteDifference < minAbsoluteDiff) {
                minAbsoluteDiff = minAbsoluteDiff;
                minItr = itr;
            }
        }
    }
    return (*minItr);
}

void Segment::prepareForRemoval() {
    for (int i = 0; i < neighbours.size();i++) {
        neighbours[i]->removeNeighbour(this);
    };
}

// TODO revisit this one
//merge segment with best survivor and remove its pointers from the neighbours
void Segment::linkSegment() {
    if(!isMarked()) {
        throw Exception();
    }
    this->masterSegment = getBestSurvivor(); // we will use this to merge segments later after linking
    this->masterSegment->neighbours.clear();
    // TODO
//    masterNode->addPixels(pixels);
//    for (vector<Segment*>::iterator itr = neighbours.begin(); itr != neighbours.end(); itr++) {
//        (*itr)->removeNeighbour(this);
//    };
    // merge neighbours too plz! and remove the masternode from the
    // not now, after
//    masterNodeItr->addNeighbours(neighbours);
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
    this->_isMarked = false;
    this->_isDead = false;
//    this->mean = 0;
//    this->variance = 0;
    this->masterSegment = 0;
}

