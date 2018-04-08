//
//  Camera.h
//  Aufgabenblatt02
//
//  Created by  on 05.10.15.
//  Copyright (c) 2015 a. All rights reserved.
//


#ifndef __Prakt2__camera__
#define __Prakt2__camera__

#include <iostream>

#include "Vector.h"

class Camera
{
private:
    float planedist;
    float width;
    float height;
    float zvalue;
    unsigned int widthInPixel;
    unsigned int heightInPixel;

public:
    Camera(float zvalue, float planedist, float width, float height,
            unsigned int widthInPixel,
           unsigned int heightInPixel);

    Vector generateRay(unsigned int x, unsigned int y) const;
    Vector position() const;

};


#endif /* defined(__Prakt2__camera__) */
