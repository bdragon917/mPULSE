#pragma once

#include "stdafx.h"

#define NOMINMAX
#define NO_SDL_GLEXT

//#include <windows.h>

#include "Shader.h"

#include "gl/glew.h"	//DONT MESS THIS ORDER!!!!
#include "gl/GLU.h"
#include "gl/GL.h"

//#include <NxPhysics.h>
//#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	int drawOverLay();
	int acceptInput(SDL_Event aEvent);
	void setBackground(bool val);

private:

	void MainMenu::setUpPerpView();	//Needs to be moved to render later

	int drawButton(int index, int texture);
	int drawBackground();
	//enum Menus { SINGLE, MULTI, STORY, CREDIT, OPTION, EXIT };
	//Menus curSelect;
	int maxSelect;	//The numbers of menus
	int curSelect;  //The current selected menu index
	bool showBG;	//Shows a background for the menu

};