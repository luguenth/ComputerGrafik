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
	Width = Width / 2;
	Height = Height / 2;
	Depth = Depth / 2;
	VB.begin();
	Vector norm = Vector(0, 0, 0);
	//Vorne X
	norm = Vector(0,0,-1);
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, -Depth, 0, 1);				// a0 x O
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, -Depth, 1, 1);			// b1 x O
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, -Depth, 0, 0);			// e2 x O
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, -Depth, 1, 0);		// f3 x O


	//Rechts
	norm = Vector(-1,0,0);
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, -Depth, 1, 1);				// a4 x ~
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, Depth, 0, 1);			// c5 x ~
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, -Depth, 1, 0);			// e6 x ~
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, Depth, 0, 0);		// g7 x ~
	
	//Links X
	norm = Vector(1, 0, 0);
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, -Depth, 0, 1);			// b8 x V
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, Depth, 1, 1);		// d9 x V
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, -Depth, 0, 0);		// f10 x V
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, Depth, 1, 0);	// h11 x V

	//Hinten X
	norm = Vector(0,0,1);
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, Depth, 0, 1);		// d12 x Ö
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, Depth, 1, 1);			// c13 x Ö
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, Depth, 1, 0);		// g14 x Ö
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, Depth, 0, 0);	// h15 x Ö

	//Oben X
	norm = Vector(0,1,0);
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, -Depth, 1, 0);			// e16 x ?
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, -Depth, 0,0);		// f17 x ?
	VB.addNormal(norm);
	addVertexWithProps(-Width, Height, Depth, 1, 1);		// g18 x ?
	VB.addNormal(norm);
	addVertexWithProps(Width, Height, Depth, 0,1);	// h19 x ?

	//Unten
	norm = Vector(0,-1,0);
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, -Depth, 1,1);				// a20 x
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, -Depth, 0,1);			// b21 x
	VB.addNormal(norm);
	addVertexWithProps(-Width, -Height, Depth, 1, 0);			// c22 x
	VB.addNormal(norm);
	addVertexWithProps(Width, -Height, Depth, 0, 0);		// d23 x
	

	VB.end();

	IB.begin();
	
	//Vorderseite
	IBaddPolygon(0, 3, 1);
	IBaddPolygon(0, 2, 3);

	//Rechte Seite
	IBaddPolygon(4, 5, 7);
	IBaddPolygon(4, 07, 06);

	//Linke Seite
	IBaddPolygon(8, 11, 9);
	IBaddPolygon(8, 10, 11);

	//Rückseite
	IBaddPolygon(12, 15, 14);
	IBaddPolygon(12, 14, 13);

	//Oben
	IBaddPolygon(17, 16,19);
	IBaddPolygon(18,19,16);

	//Unten
	IBaddPolygon(21,23,20);
	IBaddPolygon(23,22,20);

	IB.end();
}

void TriangleBoxModel::IBaddPolygon(int a, int b, int c) {
	IB.addIndex(a);
	IB.addIndex(b);
	IB.addIndex(c);
}

void TriangleBoxModel::addVertexWithProps(float x, float y, float z, float tx, float ty) {
	VB.addTexcoord0(tx, ty);
	VB.addVertex(x, y, z);				
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
