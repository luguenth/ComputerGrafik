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
	addVertexWithProps(0, 0, 0, 0, 1);				// a0 x O
	addVertexWithProps(0, 0, 0, 1, 1);				// a1 x ~
	addVertexWithProps(0, 0, 0, 0, 0);				// a2 x

	addVertexWithProps(Width, 0, 0, 1, 1);			// b3 x O
	addVertexWithProps(Width, 0, 0, 0, 1);			// b4 x V
	addVertexWithProps(Width, 0, 0, 1, 0);			// b5 x

	addVertexWithProps(0, 0, Depth, 0, 1);			// c6 x ~
	addVertexWithProps(0, 0, Depth, 1, 1);			// c7 x Ö
	addVertexWithProps(0, 0, Depth, 0, 1);			// c8 x

	addVertexWithProps(Width, 0, Depth, 1, 1);		// d9 x V
	addVertexWithProps(Width, 0, Depth, 0, 1);		// d10 x Ö
	addVertexWithProps(Width, 0, Depth, 1, 1);		// d11 x

	addVertexWithProps(0, Height, 0, 0, 0);			// e12 x O
	addVertexWithProps(0, Height, 0, 1, 0);			// e13 x ~
	addVertexWithProps(0, Height, 0, 0, 1);			// e14 x ?

	addVertexWithProps(Width, Height, 0, 1, 0);		// f15 x O
	addVertexWithProps(Width, Height, 0, 0, 0);		// f16 x V
	addVertexWithProps(Width, Height, 0, 1, 1);		// f17 x ?

	addVertexWithProps(0, Height, Depth, 0, 0);		// g18 x ~
	addVertexWithProps(0, Height, Depth, 1, 0);		// g19 x Ö
	addVertexWithProps(0, Height, Depth, 0, 0);		// g20 x ?

	addVertexWithProps(Width, Height, Depth, 1, 0);	// h21 x V
	addVertexWithProps(Width, Height, Depth, 0, 0);	// h22 x Ö
	addVertexWithProps(Width, Height, Depth, 1, 0);	// h23 x ?
	

	VB.end();

	IB.begin();
	
	//Vorderseite 0, 15, 3, 12
	IBaddPolygon(0, 15, 3);
	IBaddPolygon(0, 12, 15);

	//Rechte Seite
	IBaddPolygon(1, 6, 18);
	IBaddPolygon(1, 18, 13);

	//Linke Seite
	IBaddPolygon(4, 21, 9);
	IBaddPolygon(4, 16, 21);

	//Rückseite
	IBaddPolygon(10, 22, 19);
	IBaddPolygon(10, 19, 7);

	//Oben
	IBaddPolygon(17, 14, 23);
	IBaddPolygon(23, 14, 20);

	//Unten
	IBaddPolygon(5, 11, 2);
	IBaddPolygon(11, 8, 2);

	IB.end();
}

void TriangleBoxModel::IBaddPolygon(int a, int b, int c) {
	IB.addIndex(a);
	IB.addIndex(b);
	IB.addIndex(c);
}

void TriangleBoxModel::addVertexWithProps(float x, float y, float z, float tx, float ty) {
	VB.addTexcoord0(tx, ty);					// 0. a
	VB.addNormal(x, y, z);					// 0. a
	VB.addVertex(x, y, z);					// 0. a
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
