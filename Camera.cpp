//
//  Camera.cpp
//  Aufgabenblatt02
//
//  Created by  on 05.10.15.
//  Copyright (c) 2015 a. All rights reserved.
//



#include "Camera.h"

Camera::Camera(float zvalue, float planedist, float width, float height, unsigned int widthInPixel, unsigned int heightInPixel)
{
    this->zvalue = zvalue;
    this->planedist = planedist;
    this->width = width;
    this->height = height;
    this->widthInPixel = widthInPixel;
    this->heightInPixel = heightInPixel;
}

Vector Camera::position() const
{
	return {0, 0, this->zvalue};
};

Vector Camera::generateRay(unsigned int x, unsigned int y) const
{
	float relative_x;
    float relative_y;

    float relation_x;
    float relation_y;

    relation_x = this->width/this->widthInPixel;
    relation_y = -this->height/this->heightInPixel;

    relative_x = relation_x*x;
    relative_y = relation_y*y;

    relative_x -= (this->width / 2);
    relative_y += (this->height / 2);

    Vector ray = Vector(relative_x, relative_y, (this->zvalue+this->planedist) );
    Vector result = (ray - this->position()).normalize();

    return result;
};
