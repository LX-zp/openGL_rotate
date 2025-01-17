// Orthographic.cpp
// OpenGL SuperBible
// Demonstrates OpenGL Orthographic Projections
// Program by Richard S. Wright Jr.
#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <GLBatch.h>
#include "uart.h"
#include <process.h>
#include <math3d.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLBatch             tubeBatch;
GLBatch             innerBatch;
GLMatrixStack       modelViewMatix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;


int xRot = 0;
int yRot = 0;
int zRot = 0;

// Called to draw scene
void RenderScene(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

		
    //modelViewMatix.PushMatrix(viewFrame);
	modelViewMatix.PushMatrix();
            
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat vGray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
    //shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
    //tubeBatch.Draw();
	 
	//modelViewMatix.Translate(0.0f, 0.0f, -2.5f);

	xRot = xRot % 180;
	yRot = yRot % 180;
	zRot = zRot % 180;
	modelViewMatix.Rotate(xRot, 1.0f, 0.0f, 0.0f);
	modelViewMatix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
	modelViewMatix.Rotate(zRot, 0.0f, 0.0f, 1.0f);

	shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
	tubeBatch.Draw();

	shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vGray);
	innerBatch.Draw();

    modelViewMatix.PopMatrix();


    glutSwapBuffers();
	glutPostRedisplay();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.75f, 1.0f );

//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    shaderManager.InitializeStockShaders();
  
    
    tubeBatch.Begin(GL_QUADS, 200);
    
    float fZ = 100.0f;
    float bZ = -100.0f;

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, 100.0f);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f,50.0f,fZ);
    
    // Right Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(50.0f,-50.0f,fZ);
    
    // Top Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, 35.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 35.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, 50.0f,fZ);
    
    // Bottom Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);
    tubeBatch.Vertex3f(35.0f, -35.0f,fZ);
    
    // Top length section ////////////////////////////
    // Normal points up Y axis
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f,50.0f,bZ);
    
    // Bottom section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);
    
    // Left section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
    
    // Right Section
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);
        
    
    // Pointing straight out Z        
    // Left Panel
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);
    
    tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f,50.0f,fZ);
    
    // Right Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(50.0f,-50.0f,fZ);
    
    // Top Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, 50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, 35.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 35.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, 50.0f,fZ);
    
    // Bottom Panel
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -35.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(-35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -50.0f, fZ);
    
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 0.0f, 1.0f);	
    tubeBatch.Vertex3f(35.0f, -35.0f,fZ);
        
    // Top length section ////////////////////////////
    // Normal points up Y axis
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, 1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f,50.0f,bZ);
    
    // Bottom section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(0.0f, -1.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);
    
    // Left section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
    
    // Right Section
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, fZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);

        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
    tubeBatch.Normal3f(-1.0f, 0.0f, 0.0f);
    tubeBatch.Vertex3f(-50.0f, -50.0f, fZ);



        // Left Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f,50.0f,bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-50.0f, -50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-50.0f, 50.0f, bZ);
        
        // Right Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(50.0f,-50.0f,bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(35.0f, -50.0f, bZ);

        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);

        tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
        
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        
        tubeBatch.Vertex3f(50.0f, 50.0f, bZ);
        
        // Top Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, 50.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, 35.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, 35.0f, bZ);


        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, 50.0f, bZ);
    
        // Bottom Panel
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, -35.0f,bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(35.0f, -50.0f, bZ);
        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -50.0f, bZ);


        tubeBatch.Normal3f(0.0f, 0.0f, -1.0f);	
        tubeBatch.Color4f(1.0f, 0.0f, 0.0f, 1.0f);
        tubeBatch.Vertex3f(-35.0f, -35.0f, bZ);
    
        tubeBatch.End();


        innerBatch.Begin(GL_QUADS, 40);
 

        
        // Insides /////////////////////////////
        // Normal points up Y axis
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f,35.0f,bZ);
		
        // Bottom section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(0.0f, 1.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, fZ);
        
        // Left section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, 35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(-35.0f, -35.0f, fZ);
        
        // Right Section
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, fZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, -35.0f, bZ);
        innerBatch.Color4f(0.75f, 0.75f, 0.75f, 1.0f);
        innerBatch.Normal3f(-1.0f, 0.0f, 0.0f);
        innerBatch.Vertex3f(35.0f, 35.0f, bZ);
        
        innerBatch.End();

	}

void SpecialKeys(int key, int x, int y)
{
#if 0 
	if(key == GLUT_KEY_UP)
	{
		xRot = xRot + 10;
	}
	if(key == GLUT_KEY_DOWN)
	{
		xRot = xRot -10;
	}

	if(key == GLUT_KEY_LEFT)
	{
		yRot = yRot + 10;
	}

	if(key == GLUT_KEY_RIGHT)
	{
		yRot = yRot - 10;
	}

	if(key == GLUT_KEY_PAGE_UP)
	{
		zRot = zRot + 10;
	}

	if(key == GLUT_KEY_PAGE_DOWN)
	{
		zRot = zRot - 10;
	}


	if(key == GLUT_KEY_UP)
		viewFrame.RotateWorld(m3dDegToRad(-5.0), 1.0f, 0.0f, 0.0f);

	if(key == GLUT_KEY_DOWN)
		viewFrame.RotateWorld(m3dDegToRad(5.0), 1.0f, 0.0f, 0.0f);
        
	if(key == GLUT_KEY_LEFT)
		viewFrame.RotateWorld(m3dDegToRad(-5.0), 0.0f, 1.0f, 0.0f);
        
	if(key == GLUT_KEY_RIGHT)
		viewFrame.RotateWorld(m3dDegToRad(5.0), 0.0f, 1.0f, 0.0f);

#endif

	// Refresh the Window
	//glutPostRedisplay();
	}


void ChangeSize(int w, int h)
{
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    viewFrustum.SetOrthographic(-130.0f, 130.0f, -130.0f, 130.0f, -130.0f, 130.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
}

unsigned WINAPI thrad_uartRecive(void* param) 
{
    int x = 0, y = 0, z = 0;
	int ret=0;

	ret = openport("COM7");
	ret = setupdcb(19200);

	while (1)
	{
		ReceiveChar(&x, &y, &z);

		xRot = -y;
		yRot = z;
		zRot = x;
		printf("%d  %d  %d\n", x, y, z);
    }
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char* argv[])
{
	unsigned threadID;
	_beginthreadex(
		NULL,
		0,
		&thrad_uartRecive, //传入要操作的函数名
		NULL, //传入函数的参数
		0, 
		&threadID //用来接收创建的新线程的threadid线程号
		);

	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Orthographic Projection Example");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
        
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }
	
	//m3dTranslationMatrix44();

	SetupRC();
    
	glutMainLoop();
	return 0;
}
