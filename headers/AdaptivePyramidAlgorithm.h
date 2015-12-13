//
//  AdaptivePyramidAlgorithm.h
//  assignment-3
//
//  Created by MacBook Air on 12/9/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef assignment_3_AdaptivePyramidAlgorithm_h
#define assignment_3_AdaptivePyramidAlgorithm_h

#include "Graph.h"
#include "MatWrapper.h"

class AdaptivePyramidAlgorithm {
    Graph graph;
    int level;
    double threshold;
    int iteration;
public:
    MatWrapper * imgWrapper;
    AdaptivePyramidAlgorithm(Mat & img, double threshold);
    void init();
    void start();
    void createNodes();
    vector<Segment> getNeighbours(int x, int y);
    void setNeighbours();
    void startIteration();
    void linkSegments();
    void mergeSegments();
    void calculateMeans();
    void calculateVariances();
    void resetGraphNodesFlags();
    void removeDeadSegments();
    bool doesNeedAnotherLevel();
    bool doesNeedAnotherIteration();
};

#endif
