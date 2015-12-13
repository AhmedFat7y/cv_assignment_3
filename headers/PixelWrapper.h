//
//  PixelWrapper.h
//  assignment-3
//
//  Created by MacBook Air on 12/8/15.
//  Copyright (c) 2015 Unlimited Blade Works. All rights reserved.
//

#ifndef __assignment_3__PixelWrapper__
#define __assignment_3__PixelWrapper__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class PixelWrapper {
public:
    int x;
    int y;
    uchar value;
    //x = j, y = i
    PixelWrapper(int x, int y, uchar value);
};

#endif /* defined(__assignment_3__PixelWrapper__) */
