//
//  Tank.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Tank.h"


Tank::Tank()
{
	this->TM = new Matrix;
	this->RM = new Matrix;
	this->TM->rotationY(0);
	this->RM->rotationY(0);
	rt = 0;
	way = Vector(0,0,0);
	aim_angle = 0;
}

Tank::~Tank()
{
    // TODO: Add your code
}

bool Tank::loadModels(const char* ChassisFile, const char* CannonFile)
{
	this->pTankBot = new Model(ChassisFile, false);
	this->pTankBot->shader(new PhongShader(), true);

	this->pTankTop = new Model(CannonFile, false);
	this->pTankTop->shader(new PhongShader(), true);

    return true;
}

void Tank::steer( float ForwardBackward, float LeftRight)
{
	this->fb = ForwardBackward;
	this->lr = LeftRight;
}

void Tank::aim(const Vector& Target )
{
	Vector test = Vector(1, 0, 0);
	float test2 = atan2(test.Z, test.X) - atan2(Target.Z, Target.Y);
	float tesat = acos(way.dot(Target));
	printf("%f\n", tesat+rt);
}

void Tank::update(float dtime)
{
	Vector dir = Vector(
		cos(-rt),
		0,
		sin(-rt)
	);
	

	// -->needs dtime
	if (this->lr != 0) {
		rt = fmod(
			double(
				rt + this->lr*.01
				), 
			2*M_PI);
	}
	if (this->fb != 0) {
		way += dir*0.01*fb;
	}
	this->TM->translation(way);
	this->RM->rotationY(rt);
	this->pTankBot->transform(*this->TM * *this->RM);
	this->pTankTop->transform(*this->TM * *this->RM * Matrix().rotationY(-aim_angle));
}

void Tank::draw(const BaseCamera& Cam)
{



	this->pTankTop->draw(Cam);
	this->pTankBot->draw(Cam);

}
