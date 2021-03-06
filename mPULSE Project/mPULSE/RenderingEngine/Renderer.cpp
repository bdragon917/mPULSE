#include "Renderer.h"

Renderer::Renderer()
{
    initializeGL();
    zRot = 0.0f;
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
}

Renderer* Renderer::getInstance()
{
    static Renderer renderer;
    return &renderer;
}

///Custom Draw Functions
void Renderer::drawIE2Cylinder(float x, float y, float z, float rotX, float rotY, float rotZ, float inAngle, float inHeight)
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



void Renderer::drawCube(float x, float y, float z, float size)
{
	glPushMatrix();
	
	glTranslatef(x, y, z);
	
	
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




void Renderer::initializeGL()
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


void Renderer::createLight()
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

void Renderer::setUpPerpView()
	{
		// Switch to the projection matrix
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		int w = SCREEN_WIDTH;
		int h = SCREEN_HEIGHT;

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

////Draw Functions
//int Renderer::drawIntro(){
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glPushMatrix ();			////////
//	glLoadIdentity ();			////////
//	
//	
//	//Cameras
//	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
//	0.0,0.0,0.0,		// Look-at position 
//	0.0,1.0,0.0); 		// "Up" vector
//	
//	//set view
//	setUpPerpView();
//
//
//	glColor3f(0.75f, 0.75f, 0.75f);
//
//	glBegin(GL_QUADS);
//		glVertex3f(0,0,0);
//		glVertex3f(0.1,0,0);
//		glVertex3f(0,0.1,0);
//	glEnd();
//
//	 drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//	glFlush();
//
//	glPopMatrix();
//
//	return 1;
//
//}

//void Renderer::draw(float &testF){
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glPushMatrix ();			////////
//	glLoadIdentity ();			////////
//	
//	
//	/**
//	//Cameras
//	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
//	0.0,0.0,0.0,		// Look-at position 
//	0.0,1.0,0.0); 		// "Up" vector
//	**/
//	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + gDir.x, gEye.y + gDir.y, gEye.z + gDir.z, 0.0f, 1.0f, 0.0f);
//	//set view
//	setUpPerpView();
//
//	
//	//scene calculations
//	zRot = zRot + 0.1f;
//	if (zRot > 360.0f)
//	{zRot = 0.0f;}
//
//
//	glRotatef (10.0f, 10.0f, 0, 1);
//	//Scene transformations
//	//glRotatef (zRot, zRot, 0, 1);	///////				//The objects will rotate about the z-axis
//	
//
//	glColor3f(0.75f, 0.75f, 0.75f);
//
//	glBegin(GL_TRIANGLES);
//		glVertex3f(0,0,0);
//		glVertex3f(0.1,0,0);
//		glVertex3f(0,0.1,0);
//	glEnd();
//
//
//	//for (int i=0;i<4;i++){
//
//	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//
//	 //drawIE2Cylinder(testVal, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//
//	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//
//
//	//Draws a checkboard Ground
//	 glBegin(GL_QUADS);	
//		glColor3f(0.0f, 1.0f, 0.0f);
//		glVertex3f(-1.0,0.0,-1.0);
//		glVertex3f(0.0,0.0,-1.0);
//		glVertex3f(0.0,0.0,0.0);
//		glVertex3f(-1.0,0.0,0.0);
//
//		glColor3f(0.0f, 0.5f, 0.0f);
//		glVertex3f(0.0,0.0,-1.0);
//		glVertex3f(1.0,0.0,-1.0);
//		glVertex3f(1.0,0.0,0.0);
//		glVertex3f(0.0,0.0,0.0);
//
//		glColor3f(0.0f, 0.5f, 0.0f);
//		glVertex3f(-1.0,0.0,0.0);
//		glVertex3f(0.0,0.0,0.0);
//		glVertex3f(0.0,0.0,1.0);
//		glVertex3f(-1.0,0.0,1.0);
//
//		glColor3f(0.0f, 1.0f, 0.0f);
//		glVertex3f(0.0,0.0,0.0);
//		glVertex3f(1.0,0.0,0.0);
//		glVertex3f(1.0,0.0,1.0);
//		glVertex3f(0.0,0.0,1.0);
//	 glEnd();
//
//
//
//	 // Render all actors
//	int nbActors = gScene->getNbActors();
//	NxActor** actors = gScene->getActors();
//	while(nbActors--)
//	{
//		NxActor* actor = *actors++;
//		if(!actor->userData) continue;
//
//		float glMat[16];
//		///**
//		// Render actor
//		glPushMatrix();
//		actor->getGlobalPose().getColumnMajor44(glMat);
//		glMultMatrixf(glMat);
//		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
//		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
//		glPopMatrix();
//		//**/
//
//		///**
//		// Render shadow
//		glPushMatrix();
//		const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
//		glMultMatrixf(shadowMat);
//		glMultMatrixf(glMat);
//		glDisable(GL_LIGHTING);
//		glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
//		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
//		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
//		//**/
//		glEnable(GL_LIGHTING);
//		glPopMatrix();
//	}
//
//
//
//
//
//
//	 glFlush();
//
//
//
//	glPopMatrix();
//
//}
////


int Renderer::drawIntro2()
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