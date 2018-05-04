//
//  Tank.hpp
//  CGXcode
//
//  Created by Philipp Lensing on 16.11.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include <stdio.h>
#include <math.h>
#include "model.h"
#include "PhongShader.h"

#define M_PI 3.14159265358979323846

class Tank : public BaseModel
{
public:
    Tank();
    virtual ~Tank();
    bool loadModels(const char* ChassisFile, const char* CannonFile);
    void steer( float ForwardBackward, float LeftRight);
    void aim( const Vector& Target );
    void update(float dtime);
    virtual void draw(const BaseCamera& Cam);
protected:
	Model *pTankBot;
	Model *pTankTop;
	
	//PhongShader *pPhongShader;

	float fb;
	float lr;

	//Zurückgelegter Weg
	Vector way;

	//Winkel vom Panzer
	float rt;

	//Winkel von Kanone
	float aim_angle;

	Matrix *TM;
	Matrix *RM;
};

#endif /* Tank_hpp */
