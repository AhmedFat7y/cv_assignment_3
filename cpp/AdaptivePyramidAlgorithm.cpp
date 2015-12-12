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
        do {
            startIteration();
        } while(doesNeedAnotherIteration());
        //finished labeling all pixels/segments
        mergeSegments();
    } while(doesNeedAnotherLevel());

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
            graph.addNode(s);
        }
    }
}

void AdaptivePyramidAlgorithm::setNeighbours() {
    for(int y = 0; y < imgWrapper->height; y++) {
        for(int x = 0; x < imgWrapper->width; x++) {
            Segment &currentNode = graph.getNode(y * imgWrapper->width + x);
            vector<Point2i> neighboursIndecies = imgWrapper->getNeighbours(x, y);
            for(vector<Point2i>::iterator it = neighboursIndecies.begin(); it != neighboursIndecies.end(); it++) {
                currentNode.neighbours.push_back(&graph.nodes[it->y * imgWrapper->width + it->x]);
            }
        }
    }
}

//always call calculateMeans before calculateVariances
void AdaptivePyramidAlgorithm::calculateMeans() {
    for (vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        itr->updateMean();
    }
}

//always call calculateMeans before calculateVariances
//used for higher levels
void AdaptivePyramidAlgorithm::calculateVariances() {
    for (vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        itr->updateVariance();
    }
}


void AdaptivePyramidAlgorithm::startIteration() {
    for (vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        itr->SurviveOrKill();
//        Segment & s = *itr;
    }
}

void AdaptivePyramidAlgorithm::mergeSegments() {
    for (vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        if(itr->isDead()) {
//            Segment & masterNodeItr = itr->getBestSurvivor();


        }
    }
}

//TODO implement this method please
bool AdaptivePyramidAlgorithm::doesNeedAnotherLevel() {
    return  false;
}

//
bool AdaptivePyramidAlgorithm::doesNeedAnotherIteration() {
    for(vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        if(!itr->isMarked()) {
            return true;
        }
    }
    return false;
}
