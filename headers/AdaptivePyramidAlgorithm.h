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
public:
    MatWrapper img;
    AdaptivePyramidAlgorithm(Mat img);
    void init();
    
private:
    void createNodes();
    void setNeighbours();
};

#endif
