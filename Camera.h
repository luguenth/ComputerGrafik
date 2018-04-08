//
// Created by prof on 12.03.18.
//

#ifndef CG1_CAMERA_H
#define CG1_CAMERA_H


#include "Vector.h"

class Camera
{
public:
    Camera(float planedist, float width, float height, float zvalue, unsigned int widthInPixel, unsigned int heightInPixel);
    Vector generateRay(unsigned int x, unsigned int y);
    Vector position() const;

private:
    float planedist;
    float width;
    float height;
    float zvalue;
    unsigned int widthInPixel;
    unsigned int heightInPixel;

};


#endif //CG1_CAMERA_H
