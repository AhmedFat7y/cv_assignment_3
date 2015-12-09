//
//  Segment.cpp
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//


#include "Segment.h"

void Segment::linkPixel(PixelWrapper pixel) {
    pixels.push_back(pixel);
}

void Segment::addNeighbour(Segment segment) {
    neighbours.push_back(segment);
}
