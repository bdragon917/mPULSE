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

//#include <stdio.h>

//Physics Stuff
#include "NxPhysics.h"	//Vectors
#include "NxVec3.h"
//#include "ErrorStream.h"

//Physics
static NxPhysicsSDK*	gPhysicsSDK = NULL;
static NxScene*			gScene = NULL;
//static PrefRenderer		gPrefRenderer;

//Rendering
static NxVec3	gEye(50.0f, 50.0f, 50.0f);
static NxVec3	gDir(-0.6f,-0.2f,-0.7f);




///Game Variables
bool FrameRateLimiter = true;
float testVal = 0.0f;
enum MyGameStates { INTRO, MAINMENU, GAMEPLAY, GAMEPLAY_INIT, EXIT };
MyGameStates curState = INTRO;

float zRot = 0.0f;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


///**
//PhysX
static bool InitNx()
{
	//Initialize PhysicSDK
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, NULL);
		if(gPhysicsSDK == NULL) 
	{
		printf("\nSDK create error (%d).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode);
		return false;
	}
#if SAMPLES_USE_VRD
	// The settings for the VRD host and port are found in SampleCommonCode/SamplesVRDSettings.h
	if (gPhysicsSDK->getFoundationSDK().getRemoteDebugger())
		gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect(SAMPLES_VRD_HOST, SAMPLES_VRD_PORT, SAMPLES_VRD_EVENTMASK);
#endif

	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

	// Create a scene
	NxSceneDesc sceneDesc;
	sceneDesc.gravity				= NxVec3(0.0f, -9.81f, 0.0f);
	gScene = gPhysicsSDK->createScene(sceneDesc);
	if(gScene == NULL) 
	{
		printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
		return false;
	}

	// Set default material
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);

	// Create ground plane
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	gScene->createActor(actorDesc);

	return true;

}

//PhysX
static void ExitNx()
{
	if(gPhysicsSDK != NULL)
	{
		if(gScene != NULL) gPhysicsSDK->releaseScene(*gScene);
		gScene = NULL;
		NxReleasePhysicsSDK(gPhysicsSDK);
		gPhysicsSDK = NULL;
	}
}
//**/

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



void drawCube(float x, float y, float z, float size)
{
	glPushMatrix();
	
	glTranslatef(	x, y, z);
	
	
	float d = size / 2;

		glBegin(GL_POLYGON);
		//Bottom
		glVertex3f( d, -d, -d);
		glVertex3f( d, -d,  d);
		glVertex3f(-d, -d,  d);
		glVertex3f(-d, -d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Left
		glVertex3f(-d, -d,  d);
		glVertex3f(-d,  d,  d);
		glVertex3f(-d,  d, -d);
		glVertex3f(-d, -d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Right
		glVertex3f( d, -d, -d);
		glVertex3f( d,  d, -d);
		glVertex3f( d,  d,  d);
		glVertex3f( d, -d,  d);
		glEnd();

		glBegin(GL_POLYGON);
				//Front
		glVertex3f(-d, -d, -d);
		glVertex3f(d, -d, -d);
		glVertex3f(d, d, -d);
		glVertex3f(-d, d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Back
		glVertex3f( d, -d,  d);
		glVertex3f( d,  d,  d);
		glVertex3f(-d,  d,  d);
		glVertex3f(-d, -d,  d);
		glEnd();

		glBegin(GL_POLYGON);
				//Top
		glVertex3f( d,  d,  d);
		glVertex3f( d,  d, -d);
		glVertex3f(-d,  d, -d);
		glVertex3f(-d,  d,  d);
		glEnd();
	
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


static void CreateCube(const NxVec3& pos, int size=2, const NxVec3* initialVelocity=NULL)
{
	if(gScene == NULL) return;	

	// Create body
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;
	if(initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = NxVec3((float)size, (float)size, (float)size);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body			= &bodyDesc;
	actorDesc.density		= 10.0f;
	actorDesc.globalPose.t  = pos;
	gScene->createActor(actorDesc)->userData = (void*)size_t(size);
	//printf("Total: %d actors\n", gScene->getNbActors());
}

static void CreateTower(int size)
{
	const float cubeSize = 2.0f;
	const float spacing = 0.01f;
	NxVec3 pos(0.0f, cubeSize, 0.0f);
	while(size)
	{
		CreateCube(pos, (int)cubeSize);
		pos.y += (cubeSize * 2.0f + spacing);
		size--;
	}
}


static void CreateStack(int size)
{
	const float cubeSize = 2.0f;
	const float spacing = -2.0f*gPhysicsSDK->getParameter(NX_SKIN_WIDTH);
	NxVec3 pos(0.0f, cubeSize, 0.0f);
	float offset = -size * (cubeSize * 2.0f + spacing) * 0.5f;
	while(size)
	{
		for(int i=0;i<size;i++)
		{
			pos.x = offset + (float)i * (cubeSize * 2.0f + spacing);
			CreateCube(pos, (int)cubeSize);
		}

		offset += cubeSize;
		pos.y += (cubeSize * 2.0f + spacing);
		size--;
	}
}

static void CreateCubeFromEye(int size)
{
	NxVec3 t = gEye;
	NxVec3 vel = gDir;
	vel.normalize();
	vel*=200.0f;
	CreateCube(t, size, &vel);
}

/**
	Possible research material
**/
void draw(float &testF){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	
	/**
	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	**/
	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + gDir.x, gEye.y + gDir.y, gEye.z + gDir.z, 0.0f, 1.0f, 0.0f);
	//set view
	setUpPerpView();

	
	//scene calculations
	zRot = zRot + 0.1f;
	if (zRot > 360.0f)
	{zRot = 0.0f;}


	glRotatef (10.0f, 10.0f, 0, 1);
	//Scene transformations
	//glRotatef (zRot, zRot, 0, 1);	///////				//The objects will rotate about the z-axis
	

	glColor3f(0.75f, 0.75f, 0.75f);

	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(0.1,0,0);
		glVertex3f(0,0.1,0);
	glEnd();


	//for (int i=0;i<4;i++){

	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 //drawIE2Cylinder(testVal, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);


	//Draws a checkboard Ground
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



	 // Render all actors
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	while(nbActors--)
	{
		NxActor* actor = *actors++;
		if(!actor->userData) continue;

		float glMat[16];
		///**
		// Render actor
		glPushMatrix();
		actor->getGlobalPose().getColumnMajor44(glMat);
		glMultMatrixf(glMat);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
		glPopMatrix();
		//**/

		///**
		// Render shadow
		glPushMatrix();
		const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
		glMultMatrixf(shadowMat);
		glMultMatrixf(glMat);
		glDisable(GL_LIGHTING);
		glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
		//**/
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}






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


	//screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_FULLSCREEN );
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

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

	drawIntro2();		//Displays Loading Screen

	Uint32 start;	//For framerate

	curState = INTRO;

	//Images
	SDL_Surface* inImg = NULL;		//Used to load the image into the memory
	SDL_Surface* Optimized = NULL;	//Used to change the format to the native display format for faster display
	SDL_Surface* screen = NULL;


	//Start SDL
	//SDL_Init( SDL_INIT_EVERYTHING );
	//init();
	initializeGL();


	//Create Main Window
	SDL_WM_SetCaption("SDL TEST", "SDL_TEST");

	////Set Up a OpenGL Display
	//if ((screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN)) == NULL) {
	if ((screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
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
						CreateCubeFromEye(8);
						printf("ButtonHit0!\n");
						testVal = testVal + 0.01f;
						break;
					case 1:
						CreateCube(NxVec3(0.0f, 20.0f, 0.0f),1); 
						printf("ButtonHit1!\n");
						break;
					case 2:
						CreateStack(10);
						printf("ButtonHit2!\n");
						break;
					case 3:
						CreateTower(30);
						printf("ButtonHit3!\n");
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
					curState = GAMEPLAY_INIT;
					break;

				case MAINMENU:
					break;
				case GAMEPLAY_INIT:
					InitNx();
					curState = GAMEPLAY;
					break;
				case GAMEPLAY:
					gScene->simulate(1.0f/60.0f);
					draw(testF);
					gScene->flushStream();
					gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
					break;
				case EXIT:
					break;
			}


		// Fetch simulation results
		//gScene->flushStream();
		//gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);

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
	ExitNx();
	SDL_Quit();

	return 0;
}

