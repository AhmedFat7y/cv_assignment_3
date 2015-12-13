//
//  AdaptivePyramidAlgorithm.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/9/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "AdaptivePyramidAlgorithm.h"

AdaptivePyramidAlgorithm::AdaptivePyramidAlgorithm(Mat &img, double threshold) {
    this->imgWrapper = new MatWrapper(img);
    this->level = 0;
    this->iteration = 0;
    this->threshold = threshold;
}

void AdaptivePyramidAlgorithm::init() {
    createNodes();
    setNeighbours();
//    calculateVariancesFirstTime();
}
void AdaptivePyramidAlgorithm::start() {
    do {
        resetGraphNodesFlags();
        do {
            startIteration();
        } while(doesNeedAnotherIteration());
        //finished labeling all pixels/segments
        linkSegments();
        mergeSegments();
        updateGraphStructure();
        removeDeadSegments();
        calculateMeans();
        calculateVariances();
    } while(doesNeedAnotherLevel());

}

void AdaptivePyramidAlgorithm::applyResult() {
    for(int i=0; i < nodes.size(); i++) {
        Segment & node = nodes[i];
        for(int j=0; j <  node.pixels.size(); j++) {
            PixelWrapper & pixel = node.pixels[j];
            this->imgWrapper->set(pixel.x, pixel.y, node.mean);
        }
    }
}

//adding the pixels in sequential order
//so they can be accesed from the vector
//using same indecies as the matrix
void AdaptivePyramidAlgorithm::createNodes() {
    for(int y = 0; y < imgWrapper->height; y++) {
        for(int x = 0; x < imgWrapper->width; x++) {
            Segment s;
            s.addPixel(PixelWrapper(x, y, imgWrapper->get(x, y)));
            s.updateMean();
            //calculate variance first time using kernel window 3x3
            s.variance = imgWrapper->calculateVariance(x, y);
            addNode(s);
        }
    }
}

void AdaptivePyramidAlgorithm::setNeighbours() {
    for(int y = 0; y < imgWrapper->height; y++) {
        for(int x = 0; x < imgWrapper->width; x++) {
            Segment &currentNode = getNode(y * imgWrapper->width + x);
            vector<Point2i> neighboursIndecies = imgWrapper->getNeighbours(x, y);
            for(vector<Point2i>::iterator it = neighboursIndecies.begin(); it != neighboursIndecies.end(); it++) {
                currentNode.neighbours.push_back(&nodes[it->y * imgWrapper->width + it->x]);
            }
        }
    }
}

// always call calculateMeans before calculateVariances
void AdaptivePyramidAlgorithm::calculateMeans() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->updateMean();
    }
}

// always call calculateMeans before calculateVariances
// used for higher levels
void AdaptivePyramidAlgorithm::calculateVariances() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->updateVariance();
    }
}


void AdaptivePyramidAlgorithm::startIteration() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
        if(!itr->isMarked()) {
            itr->SurviveOrKill();
        }
    }
}

void AdaptivePyramidAlgorithm::linkSegments() {

    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr ++) {
        if(!itr->isMarked()) {
            throw Exception();
        }

        if(itr->isDead()) {
            // link segment with a survivor
            if(itr->masterSegment != 0) {
                throw Exception();
            }
            itr->linkSegment();
        }
    }
}

void AdaptivePyramidAlgorithm::mergeSegments() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr ++) {
        if(itr->isSurvivor()) {
            // do nothing for now
        } else if(itr->isDead()) {
            itr->masterSegment->addPixels(itr->pixels);
            itr->pixels.clear();
        }
    }
}

void AdaptivePyramidAlgorithm::updateGraphStructure() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr ++) {
        if(itr->isDead()) {
            itr->spreadMasterSegment();
        }
    }
}

void AdaptivePyramidAlgorithm::removeDeadSegments() {
    vector<Segment>::iterator itr = nodes.begin();
    while ( itr != nodes.end()) {
        if(!itr->isMarked()) {
            throw Exception();
        }

        if(itr->isDead()) {
            // remove node, remove it from its neighbours, move the neighbours to survivng one Node
            // all neighbours are cleared in the linksegment method
//            itr->prepareForRemoval();
            itr = nodes.erase(itr);
        } else {
            itr ++;
        }
    }
}

//TODO implement this method please
bool AdaptivePyramidAlgorithm::doesNeedAnotherLevel() {
    ++level;
    return level != 4;
}

//
bool AdaptivePyramidAlgorithm::doesNeedAnotherIteration() {
    for(vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
        if(!itr->isMarked()) {
            return true;
        }
    }
    return false;
}


void AdaptivePyramidAlgorithm::resetGraphNodesFlags() {
    for (vector<Segment>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->resetFlags();
    }
}

void AdaptivePyramidAlgorithm::addNode(Segment & segment) {
    nodes.push_back(segment);
}

Segment& AdaptivePyramidAlgorithm::getNode(int index) {
    return nodes[index];
}