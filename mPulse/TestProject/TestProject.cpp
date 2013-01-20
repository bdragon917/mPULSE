// TestProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define NOMINMAX
#include <windows.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include <NxPhysics.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>




///Game Variables
bool FrameRateLimiter = true;
float testVal = 0.0f;
enum MyGameStates { INTRO, MAINMENU, GAMEPLAY, EXIT };
MyGameStates curState = INTRO;

float zRot = 0.0f;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


///Custom Draw Functions
void drawIE2Cylinder(float x, float y, float z, float rotX, float rotY, float rotZ, float inAngle, float inHeight)
{
	glPushMatrix();
	
	glTranslatef(	x, y, z);
	glRotatef   (90.0f,	0.0f, 1.0f, 0.0f);
	glRotatef   (inAngle,	rotX, rotY, rotZ);
	
	
	GLUquadricObj* quad = gluNewQuadric();

	float base = 0.1f;
	float top = 0.1f;
	float height = inHeight;
	int slices = 12;
	int stacks = 2;
	
	gluCylinder (quad, base, top, height, slices, stacks);
	
	glPopMatrix();

}
///




void initializeGL()
{
	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_NORMALIZE);
	glEnable (GL_COLOR_MATERIAL);
	glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void createLight()
	{
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
		GLfloat mat_shininess[] = {50.0};
		GLfloat light_position[] = {1.0,1.0,1.0,0.0};
		//GLfloat light_ambient[] = {0.0,0.0,0.0,0.1};
		//GLfloat light_diffuse[] = {0.0,0.0,0.0,1.0};
		//GLfloat light_specular[] = {0.0,0.0,0.0,1.0};
		glClearColor(0.0,0.0,0.0,0.0);
		glShadeModel (GL_SMOOTH);
		
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		//glLightfv(GL_LIGHT0, GL_AMBIENT, light_position);
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_position);
		//glLightfv(GL_LIGHT0, GL_SPECULAR, light_position);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		
		
		glEnable (GL_NORMALIZE);
		glEnable (GL_COLOR_MATERIAL);
		glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	}

void setUpPerpView()
	{
		// Switch to the projection matrix
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		float w = SCREEN_WIDTH;
		float h = SCREEN_HEIGHT;

		// Set drawing to take up the entire window
		glViewport (0, 0, w, h);

		if (w > h) {
			// In this case the w/h ratio is > 1
		        float ratio = (float)w/(float)h;
				gluPerspective(60.0, ratio, 0.01, 800.0);
				//glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}
		else {
			// In this case the h/w ratio is > 1
		        float ratio = (float)h/(float)w;
				gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
				//glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}

		//Switch back to modelview matrix
		glMatrixMode (GL_MODELVIEW);
	}


//AI Stuff
void moveStuff(float &testF){
		if (testVal > 0)
		{testF = testF - 0.005f;}
		else
		{testF = testF + 0.005f;}

		testVal = testVal + testF;
}
//

//Draw Functions
int drawIntro(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	
	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	
	//set view
	setUpPerpView();


	glColor3f(0.75f, 0.75f, 0.75f);

	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(0.1,0,0);
		glVertex3f(0,0.1,0);
	glEnd();

	 drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	glFlush();

	glPopMatrix();

	return 1;

}


/**
	Possible research material
**/
void draw(float &testF){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	
	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	
	//set view
	setUpPerpView();

	
	//scene calculations
	zRot = zRot + 0.1f;
	if (zRot > 360.0f)
	{zRot = 0.0f;}

	//Scene transformations
	glRotatef (zRot, zRot, 0, 1);	///////				//The objects will rotate about the z-axis
	

	glColor3f(0.75f, 0.75f, 0.75f);

	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(0.1,0,0);
		glVertex3f(0,0.1,0);
	glEnd();


	//for (int i=0;i<4;i++){

	 drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 drawIE2Cylinder(testVal, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 drawIE2Cylinder(testVal, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 glBegin(GL_QUADS);	
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0,0.0,-1.0);
		glVertex3f(0.0,0.0,-1.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(-1.0,0.0,0.0);

		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.0,0.0,-1.0);
		glVertex3f(1.0,0.0,-1.0);
		glVertex3f(1.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);

		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-1.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,0.0,1.0);
		glVertex3f(-1.0,0.0,1.0);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(1.0,0.0,0.0);
		glVertex3f(1.0,0.0,1.0);
		glVertex3f(0.0,0.0,1.0);
	 glEnd();

	 glFlush();



	glPopMatrix();

}
//


int drawIntro2()
{
	SDL_Surface* inImg = NULL;		//Used to load the image into the memory
	SDL_Surface* Optimized = NULL;	//Used to change the format to the native display format for faster display
	SDL_Surface* screen = NULL;


	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_WM_SetCaption("SDL TEST", "SDL_TEST");


	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_FULLSCREEN );

	//Load image
	inImg = SDL_LoadBMP( "./img/loadScreen.bmp" );

	if (inImg != NULL)
	{
		Optimized = SDL_DisplayFormat(inImg);

		//Free the loaded image
		SDL_FreeSurface( inImg );
	}
	else
	{
		printf("NULL DETECTED\n");
	}

	//Apply image to screen
	SDL_BlitSurface ( Optimized, NULL, screen, NULL );

	//Update Screen
	SDL_Flip ( screen );

	//Pause
	SDL_Delay( 2000 );

	//Free the loaded image
	SDL_FreeSurface( Optimized );
	SDL_FreeSurface( screen );

	//Quit SDL
	//SDL_Quit();

	return 1;
}


//Main
int _tmain(int argc, _TCHAR* argv[])
{

	drawIntro2();

	Uint32 start;	//For framerate

	curState = INTRO;

	//Images
	SDL_Surface* inImg = NULL;		//Used to load the image into the memory
	SDL_Surface* Optimized = NULL;	//Used to change the format to the native display format for faster display
	SDL_Surface* screen = NULL;


	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );
	//init();
	initializeGL();


	//Create Main Window
	SDL_WM_SetCaption("SDL TEST", "SDL_TEST");

	////Set Up a OpenGL Display
	if ((screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN)) == NULL) {
		printf("Failed to initize graphics\n");
		return false;	
	}


	//This has to be after screen initialization
	createLight();
	setUpPerpView();

	//Initalize Controls
	SDL_Event event;

	//JoyStick initialize
	SDL_Joystick *joystick;

	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);



	float testF = 0.1f;

	//Main Program Loop
	while (!(curState == EXIT))
	{
		start=SDL_GetTicks();	//Framerate

		//AI and physic movement stuff
		moveStuff(testF);


		//Check Inputs
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				//Close
			case SDL_QUIT:
				curState = EXIT;
				break;

			//Keyboard
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					curState = EXIT;
					break;
				case SDLK_F2:
					if (FrameRateLimiter){FrameRateLimiter=false;}else{FrameRateLimiter=true;};
					break;

				}

			//Joystick
			case SDL_JOYBUTTONDOWN:
				switch (event.jbutton.button) {
					case 0:
						printf("ButtonHit!\n");
						testVal = testVal + 0.01f;
						break;
				}
			break;
			}
		}


		//Manage different drawing schemes for different states
		//Drawing calls
			switch(curState){

				case INTRO:
					drawIntro();
					//SDL_Flip ( screen );
					curState = MAINMENU;
					break;

				case MAINMENU:
					draw(testF);
				case GAMEPLAY:

				case EXIT:
					break;
			}

		//glFlush();
		//glFinish();
		SDL_GL_SwapBuffers();



		//Frame Rate Control
		if (FrameRateLimiter)
		{
			//framerate keep it at 60
			if(1000/60>(SDL_GetTicks()-start))
			{SDL_Delay(1000/60-(SDL_GetTicks()-start));}
		}

		printf("Tick Rate: %i \n",SDL_GetTicks()-start);
	}


	//Free Up stuff
	SDL_Quit();

	return 0;
}

