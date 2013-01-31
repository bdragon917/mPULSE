#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Appearance.h"

class RenderingEngine
{
public:

static RenderingEngine* getInstance();
float zRot;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
///Custom Draw Functions
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

private:
    RenderingEngine();

};