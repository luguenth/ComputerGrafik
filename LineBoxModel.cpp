//
//  LineBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "LineBoxModel.h"

LineBoxModel::LineBoxModel(float DimX, float DimY, float DimZ)
{
	
	VB.begin();

	// 0,0,0
	VB.addVertex(0, 0, 0);
	VB.addVertex(DimX, 0, 0);
	VB.addVertex(0, 0, 0);
	VB.addVertex(0, DimY, 0);
	VB.addVertex(0, 0, 0);
	VB.addVertex(0, 0, DimZ);

	//0,Y,Z
	VB.addVertex(0, DimY, DimZ);
	VB.addVertex(DimX, DimY, DimZ);
	VB.addVertex(0, DimY, DimZ);
	VB.addVertex(0, DimY, 0);
	VB.addVertex(0, DimY, DimZ);
	VB.addVertex(0, 0, DimZ);
	
	//X,Y,0
	VB.addVertex(DimX, DimY, 0);
	VB.addVertex(DimX, DimY, DimZ);
	VB.addVertex(DimX, DimY, 0);
	VB.addVertex(DimX, 0, 0);
	VB.addVertex(DimX, DimY, 0);
	VB.addVertex(0, DimY, 0);

	//X,0,Z
	VB.addVertex(DimX, 0, DimZ);
	VB.addVertex(DimX, DimY, DimZ);
	VB.addVertex(DimX, 0, DimZ);
	VB.addVertex(DimX, 0, 0);
	VB.addVertex(DimX, 0, DimZ);
	VB.addVertex(0, 0, DimZ);
	
	
	VB.end();
	
	/*
	int NumSegX = DimX;
	int NumSegY = DimY;
	int NumSegZ = DimZ;
	
	VB.begin();

	float StepX = DimX / (float)NumSegX;
	float StepZ = DimZ / (float)NumSegZ;
	float StepY = DimY / (float)NumSegY;

	float BeginX = -DimZ / 2.0f;
	float BeginZ = -DimX / 2.0f;
	float BeginY = -DimY / 2.0f;

	for (int i = 0; i <= NumSegX; ++i)
	{
		VB.addVertex(BeginZ + i * StepX, BeginY, BeginX);
		VB.addVertex(BeginZ + i * StepX, BeginY, -BeginX);
	}
	for (int i = 0; i <= NumSegZ; ++i)
	{
		VB.addVertex(BeginZ, BeginY, BeginX + i * StepY);
		VB.addVertex(-BeginZ, BeginY, BeginX + i * StepY);
	}
	for (int i = 0; i <= NumSegY; ++i)
	{
		VB.addVertex(BeginZ, BeginY + i * StepZ, BeginX);
		VB.addVertex(-BeginZ, BeginY + i * StepZ, BeginX);
	}

	VB.end();
	*/
	
}

void LineBoxModel::draw(const BaseCamera& Cam)
{
	
	BaseModel::draw(Cam);

	VB.activate();

	glDrawArrays(GL_LINES, 0, VB.vertexCount());

	VB.deactivate();
	
}
