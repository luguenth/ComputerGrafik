//
//  Application.cpp
//  ogl4
//
//  Created by Philipp Lensing on 16.09.16.
//  Copyright © 2016 Philipp Lensing. All rights reserved.
//

#include "Application.h"
#ifdef WIN32
#include <GL/glew.h>
#include <glfw/glfw3.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw/glfw3.h>
#endif
#include "lineplanemodel.h"
#include "triangleplanemodel.h"
#include "trianglespheremodel.h"
#include "lineboxmodel.h"
#include "triangleboxmodel.h"
#include "model.h"
#include "scene.h"


#ifdef WIN32
#define ASSET_DIRECTORY "../../assets/"
#else
#define ASSET_DIRECTORY "../assets/"
#endif


Application::Application(GLFWwindow* pWin) : pWindow(pWin), Cam(pWin)
{
    BaseModel* pModel;
    ConstantShader* pConstShader;
    PhongShader* pPhongShader;
    
    // create LineGrid model with constant color shader
    pModel = new LinePlaneModel(10, 10, 10, 10);
    pConstShader = new ConstantShader();
	pConstShader->color( Color(1,1,1));
    pModel->shader(pConstShader, true);
    Models.push_back( pModel );
	/*
    // Exercise 1
	pTankBot = new Model(ASSET_DIRECTORY "tank_bottom.dae", false);
	pTankBot->shader(new PhongShader(), true);
	Models.push_back(pTankBot);
    
	pTankTop = new Model(ASSET_DIRECTORY "tank_top.dae", false);
	pTankTop->shader(new PhongShader(), true);
	Models.push_back(pTankTop);
   */

    // Exercise 2
    
    pPhongShader = new PhongShader();
    pTank = new Tank();
    pTank->shader(pPhongShader, true);
    pTank->loadModels(ASSET_DIRECTORY "tank_bottom.dae", ASSET_DIRECTORY "tank_top.dae");
    Models.push_back( pTank );
 
    
    // Exercise 3
    /*
    Scene* pScene = new Scene();
    pScene->shader(new PhongShader(), true);
    pScene->addSceneFile(ASSET_DIRECTORY "scene.osh");
    Models.push_back(pScene);
    */
    

    
}
void Application::start()
{
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Application::update()
{
	/*
    // Exercise 1
	Matrix TM;
	TM.translation(4,0,0);
	Matrix RM_1;
	Matrix RM_2;
	Matrix RM_3;
	RM_1.rotationY(-glfwGetTime());
	RM_2.rotationY(-0.5f*3.14);
	RM_3.rotationY(glfwGetTime());
	
	Matrix RTM_bot = RM_1 * TM * RM_2;
	Matrix TRM = RTM_bot * RM_3;
	pTankBot->transform(RTM_bot);
	pTankTop->transform(TRM);
	*/

    // Exercise 2
    // TODO: add your code here
	float fb = 0, lr = 0;

	if (glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS) fb = 1.0f;
	if (glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS) fb = -1.0f;
	if (glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) lr = 1.0f;
	if (glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) lr = -1.0f;

	pTank->steer(fb, lr);
	
	double xpos, ypos;
	glfwGetCursorPos(pWindow, &xpos, &ypos);
	Vector temp = Vector();
	
	pTank->aim(
		calc3DRay(xpos, ypos, temp)
	);

	pTank->update(glfwGetTime());

	
    Cam.update();
}

Vector Application::calc3DRay( float x, float y, Vector& Pos)
{
	int width, height;
	glfwGetWindowSize(pWindow, &width, &height);
	double xnorm = 2.0 / (width);
	double ynorm = 2.0 / (height);
	x = 1 - x * xnorm;
	y = 1 - y * ynorm;

	Matrix pMatrix = Cam.getProjectionMatrix();
	Pos = Vector(x, y, 0);
	Pos = pMatrix.invert() * Pos;

	Matrix vMatrix = Cam.getViewMatrix();
	vMatrix.transpose();
	Pos = vMatrix * Pos;

	float s = 0;
	
	Cam.position().triangleIntersection(Pos, Vector(1, 0, 0), Vector(0, 0, 0), Vector(0, 0, 1), s);

	Pos = Cam.position() + Pos * s;

    return Pos; // dummy return value
}

void Application::draw()
{
    // 1. clear screen
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. setup shaders and draw models
    for( ModelList::iterator it = Models.begin(); it != Models.end(); ++it )
    {
        (*it)->draw(Cam);
    }
    
    // 3. check once per frame for opengl errors
    GLenum Error = glGetError();
    assert(Error==0);
}
void Application::end()
{
    for( ModelList::iterator it = Models.begin(); it != Models.end(); ++it )
        delete *it;
    
    Models.clear();
}