//
// Created by prof on 12.03.18.
//

#include <cmath>
#include "Camera.h"

Camera::Camera(float planedist, float width, float height, float zvalue, unsigned int widthInPixel, unsigned int heightInPixel)
        : planedist(planedist),
          width(width),
          height(height),
          zvalue(std::fabs(zvalue)),    //TODO: Better make 0 if neg?
          widthInPixel(widthInPixel),
          heightInPixel(heightInPixel)
{}

Vector Camera::generateRay(unsigned int x, unsigned int y) {
    float scaleHeight = height/heightInPixel;
    float scaleWidth = width/widthInPixel;
    Vector temp = (Vector(
            x*scaleWidth,
            y*scaleHeight,
            zvalue-planedist
    ) -position())
            .normalize();
    return temp;

}

Vector Camera::position() const {
    return Vector(0,0,zvalue);
}


