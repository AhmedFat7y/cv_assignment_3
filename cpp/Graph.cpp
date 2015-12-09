//
//  Graph.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#include "Graph.h"

void Graph::addNode(Segment segment) {
    nodes.push_back(segment);
}

Segment Graph::getNode(int index) {
    return nodes[index];
}