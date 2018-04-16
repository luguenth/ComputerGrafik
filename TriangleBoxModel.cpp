//
//  TriangleBoxModel.cpp
//  CGXcode
//
//  Created by Philipp Lensing on 10.10.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "TriangleBoxModel.h"

TriangleBoxModel::TriangleBoxModel(float Width, float Height, float Depth)
{
	VB.begin();
	VB.addTexcoord0(0,0);					// 0. a
	VB.addNormal(0, 0, 0);					// 0. a
	VB.addVertex(0, 0, 0);					// 0. a
	VB.addTexcoord0(Width,0);				// 1. b	
	VB.addNormal(Width, 0, 0);				// 1. b	
	VB.addVertex(Width, 0, 0);				// 1. b	
	VB.addTexcoord0(0,0);				// 2. c
	VB.addNormal(0, 0, Depth);				// 2. c
	VB.addVertex(0, 0, Depth);				// 2. c
	VB.addTexcoord0(Width,0);			// 3. d
	VB.addNormal(Width, 0, Depth);			// 3. d
	VB.addVertex(Width, 0, Depth);			// 3. d
	VB.addTexcoord0(0, Height);			// 4. e	
	VB.addNormal(0, Height, 0);				// 4. e	
	VB.addVertex(0, Height, 0);				// 4. e	
	VB.addTexcoord0(Width, Height);			// 5. f
	VB.addNormal(Width, Height, 0);			// 5. f
	VB.addVertex(Width, Height, 0);			// 5. f
	VB.addTexcoord0(0,Height);			// 6. g
	VB.addNormal(0, Height, Depth);			// 6. g
	VB.addVertex(0, Height, Depth);			// 6. g
	VB.addTexcoord0(Width, Height);     // 7. h
	VB.addNormal(Width, Height, Depth);     // 7. h
	VB.addVertex(Width, Height, Depth);     // 7. h
	

	VB.end();

	IB.begin();
	
	//Vorderseite
	IB.addIndex(0);
	IB.addIndex(5);
	IB.addIndex(1);

	IB.addIndex(0);
	IB.addIndex(4);
	IB.addIndex(5);

	//Rechte Seite
	IB.addIndex(0);
	IB.addIndex(2);
	IB.addIndex(6);

	IB.addIndex(0);
	IB.addIndex(6);
	IB.addIndex(4);

	//Linke Seite
	IB.addIndex(1);
	IB.addIndex(7);
	IB.addIndex(3);

	IB.addIndex(1);
	IB.addIndex(5);
	IB.addIndex(7);
	
	//Hinterseite
	IB.addIndex(3);
	IB.addIndex(7);
	IB.addIndex(6);

	IB.addIndex(3);
	IB.addIndex(6);
	IB.addIndex(2);

	//Oben
	IB.addIndex(5);
	IB.addIndex(4);
	IB.addIndex(7);

	IB.addIndex(7);
	IB.addIndex(4);
	IB.addIndex(6);

	//Unten
	IB.addIndex(1);
	IB.addIndex(3);
	IB.addIndex(0);

	IB.addIndex(3);
	IB.addIndex(2);
	IB.addIndex(0);
	IB.end();
}

void TriangleBoxModel::draw(const BaseCamera& Cam)
{
	BaseModel::draw(Cam);

	VB.activate();
	IB.activate();
	//glDrawArrays(GL_TRIANGLES, 0, IB.indexCount());
	glDrawElements(GL_TRIANGLES, IB.indexCount(), IB.indexFormat(), 0);
	IB.deactivate();
	VB.deactivate();
    
}
