#pragma once

#define NOMINMAX
#define NO_SDL_GLEXT



#include "gl/glew.h"	//DONT MESS THIS ORDER!!!!
#include "gl/GLU.h"
#include "gl/GL.h"

#include "Shader.h"

#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "GL\glut.h"			//For text
#include "Appearance.h"


class RenderingEngine
{
public:

static RenderingEngine* getInstance();
float zRot;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
///Custom Draw Functions
void prints(char* s);
void drawCube(float x, float y, float z, float size);
void initializeGL();
void createLight();
void setUpPerpView();
void drawIE2Cylinder(float x, float y, float z, float rotX, float rotY, float rotZ, float inAngle, float inHeight);
//Draw Functions
int drawIntro();
void render(Appearance* appearance);
void draw();
int drawIntro2();
void moveStuff(float &testF);


    Shader* aShader;
private:
    RenderingEngine();

//    int loadShaders();
        //Used to generate a list of shaders
 //       typedef enum {
 //       CAR
 //   } ShaderType;
    
 //   CONST int ShaderTypeNum = 1;



};