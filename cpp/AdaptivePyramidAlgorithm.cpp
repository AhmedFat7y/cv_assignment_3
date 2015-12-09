//
//  AdaptivePyramidAlgorithm.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/9/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include <stdio.h>
#include "AdaptivePyramidAlgorithm.h"

AdaptivePyramidAlgorithm::AdaptivePyramidAlgorithm(Mat img) {
    this->img = MatWrapper(&img);
}

void AdaptivePyramidAlgorithm::init() {
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
        }
    }
}



void AdaptivePyramidAlgorithm::setNeighbours() {
    for(int y = 0; y < img.height; y++) {
        for(int x = 0; x < img.width; x++) {
            Segment currentNode = graph.getNode(y * img.width + x);
            vector<Point2i> neighbours = img.getNeibours(x, y);
            for(vector<Point2i>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
                currentNode.addNeighbour(graph.getNode(it->y * img.width + it->x));
            }
        }
    }
}

void 

