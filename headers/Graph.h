//
//  Graph.h
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef __assignment_3__Graph__
#define __assignment_3__Graph__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include "Segment.h"

using namespace cv;
using namespace std;


class Graph {
public:
    vector<Segment> nodes;
    void addNode(Segment segment);
    Segment getNode(int index);
};


#endif /* defined(__assignment_3__Graph__) */
