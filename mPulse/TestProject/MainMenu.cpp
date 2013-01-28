/**
	Use initial to generate a full menu
	
	Use draw without initial to draw menu overlay?

	-Should be able to draw main menu or menu overlay
	-Should also be able to accept controls, and allow different menu selections
**/
#include "stdafx.h"
#include "MainMenu.h"

//** TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//depriated, should look at render for this method later
void MainMenu::setUpPerpView()
	{
		// Switch to the projection matrix
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		float w = 640;
		float h = 480;

		// Set drawing to take up the entire window
		glViewport (0, 0, w, h);

		if (w > h) {
			// In this case the w/h ratio is > 1
		        float ratio = (float)w/(float)h;
				//gluPerspective(60.0, ratio, 0.01, 800.0);
				gluPerspective(60.0, ratio, 1.0f, 10000.0f);
				//glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}
		else {
			// In this case the h/w ratio is > 1
		        float ratio = (float)h/(float)w;
				//gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
				gluPerspective(60.0, ratio, 1.0/ratio, 10000.0f);
				//glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}

		//Switch back to modelview matrix
		glMatrixMode (GL_MODELVIEW);
	}


 //TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! **/






MainMenu::MainMenu()
{
	maxSelect = 4;	//The numbers of menus	//THIS NEEDS TO BE MANUALLY UPDATED TO NUMBER OF BUTTONS ON SCREEN!

	curSelect = 0;  //The current selected menu index
	showBG = false;	//Shows a background for the menu
}
MainMenu::~MainMenu()
{

}

void MainMenu::setBackground(bool val)
{
	showBG = val;
}
//Draws a button (offset, index, texture??
int MainMenu::drawButton(int index, int texture)
{

	const float button_width = 0.33f;
	const float button_height = 0.125f;
	const float bottom_pad = 0.2f;
	//1 = offset //using index as offset
	float LocOffset = index * button_width;


		glBegin(GL_QUADS);
		

		if (index == curSelect)	//If selected, change looks!
		{glColor3f(1.0f, 0.0f, 0.0f);}
		else
		{glColor3f(0.0f, 1.0f, 0.0f);}
		

		//tl, tr, br, bl 
		glVertex3f(	-1.0 + LocOffset,
					-1.0 + button_height + bottom_pad,
					0);

		glVertex3f(	-1.0 + LocOffset + button_width,
					-1.0 + button_height + bottom_pad,
					0);

		glVertex3f(	-1.0 + LocOffset + button_width,
					-1.0 + bottom_pad,
					0);

		glVertex3f(	-1.0 + LocOffset,
					-1.0 + bottom_pad,
					0);

		glEnd();

		return 0;
}


int MainMenu::drawBackground()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 0;
}

//Textures is assumed to be loaded to slots: 
int MainMenu::drawOverLay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);			//This might allow transparent pause screen, requires more research!

	if (showBG) {drawBackground();}	//draws background if enabled

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	

	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector

	//set view
	setUpPerpView();




	//Draws a checkboard Ground
	 drawButton(0, 0);		//Single
	 drawButton(1, 0);		//Multi
	 drawButton(2, 0);		//Story
	 drawButton(3, 0);		//Option
	 drawButton(4, 0);		//Exit

	glFlush();
	glPopMatrix();

	return 0;
}



//Returns 1 if quiting menu
//returns 0 otherwise
int MainMenu::acceptInput(SDL_Event aEvent)
{

	int ret = 0;
//Check Inputs
		//if (SDL_PollEvent(&aEvent))
		{
			switch (aEvent.type)
			{
				//Close
				case SDL_QUIT:
					break;

				//Keyboard
				case SDL_KEYDOWN:
					switch (aEvent.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							ret = 1;
							//curState = EXIT;
							break;
						case SDLK_LEFT:
							if (curSelect > 1){curSelect = curSelect - 1;}else{curSelect = maxSelect;};printf("curSelected:%i\n",curSelect);
							break;
					
						case SDLK_RIGHT:
							if (curSelect < maxSelect){curSelect = curSelect + 1;}else{curSelect = 0;};printf("curSelected:%i\n",curSelect);
							break;
					}

				//Joystick
				case SDL_JOYBUTTONDOWN:
					switch (aEvent.jbutton.button)
					{
						case 0:
							break;
						case 1:
							break;
						case 2:
							break;
						case 3:
							break;

					}
			break;
			}
		}

	return ret;
}

//private:
//	enum Menus { SINGLE, MULTI, STORY, CREDIT, OPTION, EXIT };
//	Menus curSelect;