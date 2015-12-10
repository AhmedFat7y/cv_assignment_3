//
//  AdaptivePyramidAlgorithm.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/9/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "AdaptivePyramidAlgorithm.h"

AdaptivePyramidAlgorithm::AdaptivePyramidAlgorithm(Mat img, double threshold) {
    this->img = MatWrapper(&img);
    this->level = 0;
    this->threshold = threshold;
}

void AdaptivePyramidAlgorithm::init() {
    createNodes();
    setNeighbours();
}

//adding the pixels in sequential order
//so they can be accesed from the vector
//using same indecies as the matrix
void AdaptivePyramidAlgorithm::createNodes() {
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            Segment s;
            PixelWrapper p(x, y, img.get(x, y));
            s.linkPixel(p);
            graph.addNode(s);
            s.updateMean();
        }
    }
}

void AdaptivePyramidAlgorithm::setNeighbours() {
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            Segment currentNode = graph.getNode(y * img.width + x);
            currentNode.addNeighbours(getNeighbours(x, y));
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
void AdaptivePyramidAlgorithm::calculateVariances() {
    for (vector<Segment>::iterator itr = graph.nodes.begin(); itr != graph.nodes.end(); itr++) {
        itr->updateVariance();
    }
}

vector<Segment> AdaptivePyramidAlgorithm::getNeighbours(int x, int y) {
    vector<Point2i> neighboursIndecies = img.getNeighbours(x, y);
    vector<Segment> neighbours(neighboursIndecies.size());
    for(vector<Point2i>::iterator it = neighboursIndecies.begin(); it != neighboursIndecies.end(); it++) {
        neighbours.push_back(graph.getNode(it->y * img.width + it->x));
    }
    return neighbours;
}

bool AdaptivePyramidAlgorithm::doesNeedAnotherLevel() {
    calculateMeans();
    return  false;
}
