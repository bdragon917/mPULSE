#include "RenderingEngine.h"


RenderingEngine::RenderingEngine()
{
    zRot = 0.0f;
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
	setUpPerpView();
	createLight();
	initializeGL();

    testVal = 0.0f;

}

RenderingEngine* RenderingEngine::getInstance()
{
    static RenderingEngine renderer;
    return &renderer;
}




//Texture Stuff
void RenderingEngine::bindBMPtoTexture(char* filename, GLuint *textures)
{
	unsigned char *data = 0;
	BMPImg aBMPImg;
	int width;
	int height;

	//"/img/textureTest.bmp"

	int err = aBMPImg.Load(filename);
	if (!(err == 1))
	{printf("Error: Loading Texture: %i\n", err);}
	data = aBMPImg.GetImg();
	width = aBMPImg.GetWidth();
	height = aBMPImg.GetHeight();

	glGenTextures(1, &textureid_P1);

	glBindTexture(GL_TEXTURE_2D, textureid_P1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}
/**
	To-be moved to Render Initialization Method
	requires openGL,  BMP.h, 
**/

void RenderingEngine::initializeTexture()
{
	//bindBMPtoTexture("./img/textureTest.bmp", textureid_P1);
	///**
	unsigned char *data = 0;
	BMPImg aBMPImg;
	int width;
	int height;

	//"/img/textureTest.bmp"

	int err = aBMPImg.Load("./img/testT.bmp");
	if (!(err == 1))
	{printf("Error: Loading Texture: %i\n", err);}
	data = aBMPImg.GetImg();
	width = aBMPImg.GetWidth();
	height = aBMPImg.GetHeight();
	//aBMPImg.GetImg
	//LoadPicture(data);

	//glEnable (GL_TEXTURE_2D);		//Don't need this, since shader programs will control texture usage
	glGenTextures(1, &textureid_P1);

	glBindTexture(GL_TEXTURE_2D, textureid_P1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//**/


	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Unallocation data


	// select modulate to mix texture with color for shading
	//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	// when texture area is small, bilinear filter the closest mipmap
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	//				 GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the original
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// the texture wraps over at the edges (repeat)
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

}



///Custom Draw Functions


//This function converts an int into a string
string RenderingEngine::FloatToString(float input)
{
	stringstream stream;
	stream << input;
	return stream.str();
}

/**
*	This draws a string on screen
**/
void RenderingEngine::prints(string s)
{

     glDisable(GL_LIGHTING);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(70, 1, 1, 100);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
//gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);

    //(x,y) is from the bottom left of the window
///**
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    glScalef(0.1, 0.1, 0.1);

    float x = 10;
    float y = SCREEN_HEIGHT - 20;
    glTranslatef(x*10.0f, y*10.0f, 0.0f);
    //glRasterPos2i(10,10);     //not important i guess??


     for (int i=0; i < s.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    }

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


     glEnable(GL_LIGHTING);

    /**
    glPushMatrix ();			////////
	glLoadIdentity ();			////////

    setUpOrthoView();
	//  Fonts
	//  GLUT_BITMAP_9_BY_15,
    //  GLUT_BITMAP_8_BY_13,
    //  GLUT_BITMAP_TIMES_ROMAN_10,
     // GLUT_BITMAP_TIMES_ROMAN_24,
    //  GLUT_BITMAP_HELVETICA_10,
    //  GLUT_BITMAP_HELVETICA_12,
     // GLUT_BITMAP_HELVETICA_18  


	 glDisable(GL_TEXTURE_2D);

	   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
         //glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
         s++;
      }
   }

       glPopMatrix();
       */

}

void RenderingEngine::drawIE2Cylinder(float x, float y, float z, float rotX, float rotY, float rotZ, float inAngle, float inHeight)
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



void RenderingEngine::drawCube(float x, float y, float z, float size)
{
	glPushMatrix();
	
	glTranslatef(	x, y, z);
	
	
	float d = size / 2;

		glBegin(GL_POLYGON);
		//Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( d, -d, -d);
		glTexCoord2d(1.0,0.0); glVertex3f( d, -d,  d);
		glTexCoord2d(1.0,1.0); glVertex3f(-d, -d,  d);
		glTexCoord2d(0.0,1.0); glVertex3f(-d, -d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Left
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(-d, -d,  d);
		glTexCoord2d(1.0,0.0); glVertex3f(-d,  d,  d);
		glTexCoord2d(1.0,1.0); glVertex3f(-d,  d, -d);
		glVertex3f(-d, -d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Right
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( d, -d, -d);
		glTexCoord2d(1.0,0.0); glVertex3f( d,  d, -d);
		glTexCoord2d(1.0,1.0); glVertex3f( d,  d,  d);
		glTexCoord2d(0.0,1.0); glVertex3f( d, -d,  d);
		glEnd();

		glBegin(GL_POLYGON);
				//Front
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(-d, -d, -d);
		glTexCoord2d(1.0,0.0); glVertex3f(d, -d, -d);
		glTexCoord2d(1.0,1.0) ;glVertex3f(d, d, -d);
		glTexCoord2d(0.0,1.0); glVertex3f(-d, d, -d);
		glEnd();

		glBegin(GL_POLYGON);
				//Back
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( d, -d,  d);
		glTexCoord2d(1.0,0.0); glVertex3f( d,  d,  d);
		glTexCoord2d(1.0,1.0) ;glVertex3f(-d,  d,  d);
		glTexCoord2d(0.0,1.0); glVertex3f(-d, -d,  d);
		glEnd();

		glBegin(GL_POLYGON);
				//Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( d,  d,  d);
		glTexCoord2d(1.0,0.0); glVertex3f( d,  d, -d);
		glTexCoord2d(1.0,1.0); glVertex3f(-d,  d, -d);
		glTexCoord2d(0.0,1.0); glVertex3f(-d,  d,  d);
		glEnd();
	
	glPopMatrix();

}
///




void RenderingEngine::initializeGL()
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


    
    initializeTexture();

    //int err = glewInit();               //Needs a window to execute successfully
	
   // if (err == GLEW_OK)
	//	{printf("glewInit is successful!\n");aShader = new Shader("shaders/texture.frag", "shaders/texture.vert");}
    //else
    //{fprintf(stderr, "Error: %s\n", glewGetErrorString(err));//printf("%i\n",err);
    //}
    
    
    
    

}


void RenderingEngine::createLight()
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

void RenderingEngine::setUpPerpView()
	{
		// Switch to the projection matrix
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();

		int w = SCREEN_WIDTH;
		int h = SCREEN_HEIGHT;

		//int w = 640;
		//int h = 480;

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


void RenderingEngine::setUpOrthoView()
	{
		// Switch to the projection matrix
		//glMatrixMode (GL_PROJECTION);
        glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();

		int w = SCREEN_WIDTH;
		int h = SCREEN_HEIGHT;

		//int w = 640;
		//int h = 480;

		// Set drawing to take up the entire window
		glViewport (0, 0, w, h);

		if (w > h) {
			// In this case the w/h ratio is > 1
		        float ratio = (float)w/(float)h;
				//gluPerspective(60.0, ratio, 0.01, 800.0);
				//gluPerspective(60.0, ratio, 1.0f, 10000.0f);
				glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}
		else {
			// In this case the h/w ratio is > 1
		        float ratio = (float)h/(float)w;
				//gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
				//gluPerspective(60.0, ratio, 1.0/ratio, 10000.0f);
				glOrtho (-ratio, ratio, -1, 1, -10, 10);
		}

		//Switch back to modelview matrix
		glMatrixMode (GL_MODELVIEW);
	}

//Draw Functions
int RenderingEngine::drawIntro(){
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

	// drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	glFlush();

	glPopMatrix();

	return 1;

}

void RenderingEngine::draw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	///**
	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	//**/
	
	//set view
	setUpPerpView();

	
	//scene calculations
//	zRot = zRot + 0.1f;		//Changing this variable seems to cause problems. Also seen in WIDTH and HEIGHT
//	if (zRot > 360.0f)
//	{zRot = 0.0f;}


	glRotatef (10.0f, 10.0f, 0, 1);
	//Scene transformations
	//glRotatef (zRot, zRot, 0, 1);	///////				//The objects will rotate about the z-axis
	

	glColor3f(0.75f, 0.75f, 0.75f);

    ///*
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(0.1,0,0);
		glVertex3f(0,0.1,0);
	glEnd();
   //*/

	//for (int i=0;i<4;i++){

	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 //drawIE2Cylinder(testVal, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	 //drawIE2Cylinder(testVal, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    //*
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
     //*/

     //aShader->on();
     glColor3f(1.0f, 1.0f, 1.0f);
     //drawCube(0.0f,0.0f,0.0f,1.0f);
    // aShader->off();



	 //glRasterPos3f(0.0f ,0.0f , 0.0f);
	 glColor3f(1.0f,1.0f,1.0f);
	 prints("LETE THERE BE TEXT!!!!!!!!! %i \n DALKJDSLJDKLASDJSKj");

	 /**
	 glRasterPos2i(300,0);
	 glColor3f(1.0f,1.0f,1.0f);
	 prints("3, 0 LETE THERE BE TEXT!!!!!!!!! %i \n DALKJDSLJDKLASDJSKj");

	 glRasterPos2i(0,200);
	 glColor3f(1.0f,1.0f,1.0f);
	 prints("0, 2 LETE THERE BE TEXT!!!!!!!!! %i \n DALKJDSLJDKLASDJSKj");

	 glRasterPos2i(300,200);
	 glColor3f(1.0f,1.0f,1.0f);
	 prints("3, 2 LETE THERE BE TEXT!!!!!!!!! %i \n DALKJDSLJDKLASDJSKj");
	 **/
	 // Render all actors
	//int nbActors = gScene->getNbActors();
	//NxActor** actors = gScene->getActors();
	//while(nbActors--)
	//{
	//	NxActor* actor = *actors++;
	//	if(!actor->userData) continue;

	//	float glMat[16];
	//	///**
	//	// Render actor
	//	glPushMatrix();
	//	actor->getGlobalPose().getColumnMajor44(glMat);
	//	glMultMatrixf(glMat);
	//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//	//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
	//	drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
	//	glPopMatrix();
	//	//**/

	//	///**
	//	// Render shadow
	//	glPushMatrix();
	//	const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
	//	glMultMatrixf(shadowMat);
	//	glMultMatrixf(glMat);
	//	glDisable(GL_LIGHTING);
	//	glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
	//	//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
	//	drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);
		//**/
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

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


void RenderingEngine::drawTest(float deltaTime)
    {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	///**
	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	//**/
	
	//set view
	setUpPerpView();

	glRotatef (10.0f, 10.0f, 0, 1);
	//Scene transformations
	//glRotatef (testVal, 0, 0, 1);	///////				//The objects will rotate about the z-axis
	
    testVal = testVal + 0.5f;


	glColor3f(0.75f, 0.75f, 0.75f);

    ///*
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(0.1,0,0);
		glVertex3f(0,0.1,0);
	glEnd();

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
     //*/

     glColor3f(1.0f, 1.0f, 1.0f);

     char shaded = 'f';

     if (!(aShader == NULL))
     {aShader->on();shaded = 't';}

     drawCube(0,0.5,0,1.0f);

     if (!(aShader == NULL))
     {aShader->off();}


	 //glRasterPos3f(0.0f ,0.0f , 0.0f);
	 glColor3f(1.0f,1.0f,1.0f);

     string disStr = "Current FPS: " + FloatToString(deltaTime) + " Shader:" + shaded;

    
	 prints(disStr);


		glEnable(GL_LIGHTING);
		glPopMatrix();
    }


int RenderingEngine::drawIntro2()
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



void RenderingEngine::drawScene(NxScene* scene)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	
	//Cameras
	gluLookAt(0.0,0.0,10.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	
	//set view
	setUpPerpView();

	glRotatef (10.0f, 10.0f, 0, 1);
	//Scene transformations
	//glRotatef (testVal, 0, 0, 1);	///////				//The objects will rotate about the z-axis
	
    testVal = testVal + 0.5f;


	glColor3f(0.75f, 0.75f, 0.75f);

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

     glColor3f(1.0f, 1.0f, 1.0f);

     char shaded = 'f';

     if (!(aShader == NULL))
     {aShader->on();shaded = 't';}

			// Render all actors
	int nbActors = scene->getNbActors();
	NxActor** actors = scene->getActors();
	while(nbActors--)
	{
		//printf("Hello!");
		NxActor* actor = *actors++;
		//if(!actor->userData) continue;

		float glMat[16];

		// Render actor
		glPushMatrix();
		printf("X Position: %f", actor->getGlobalPosition().x);
		printf("  Y Position: %f", actor->getGlobalPosition().y);
		printf("  Z Position: %f\n", actor->getGlobalPosition().z);
		actor->getGlobalPose().getColumnMajor44(glMat);
		
		glMultMatrixf(glMat);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		glPopMatrix();

		drawCube(0, 0, 0, 0.5f*2.0f);

		// Render shadow
		glPushMatrix();
		const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
		glMultMatrixf(shadowMat);
		glMultMatrixf(glMat);
		glDisable(GL_LIGHTING);
		glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);

		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

     if (!(aShader == NULL))
     {aShader->off();}


	 //glRasterPos3f(0.0f ,0.0f , 0.0f);
	 glColor3f(1.0f,1.0f,1.0f);



	glEnable(GL_LIGHTING);
	glPopMatrix();









/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();			////////
	glLoadIdentity ();			////////
	

	//Cameras
	gluLookAt(0.0,0.0,2.0,  // Eye/camera position
	0.0,0.0,0.0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector

	
	//set view
	setUpPerpView();

	glRotatef (10.0f, 10.0f, 0, 1);
	//Scene transformations
	//glRotatef (zRot, zRot, 0, 1);	///////				//The objects will rotate about the z-axis
	
	glColor3f(0.75f, 0.75f, 0.75f);

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
     //

     //aShader->on();
     glColor3f(1.0f, 1.0f, 1.0f);
     //drawCube(0.0f,0.0f,0.0f,1.0f);
    // aShader->off();



	 //glRasterPos3f(0.0f ,0.0f , 0.0f);
	 glColor3f(1.0f,1.0f,1.0f);
	 prints("LETE THERE BE TEXT!!!!!!!!! %i \n DALKJDSLJDKLASDJSKj");

	// Render all actors
	int nbActors = scene->getNbActors();
	NxActor** actors = scene->getActors();
	while(nbActors--)
	{
		NxActor* actor = *actors++;
		if(!actor->userData) continue;

		float glMat[16];

		// Render actor
		glPushMatrix();
		actor->getGlobalPose().getColumnMajor44(glMat);
		glMultMatrixf(glMat);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		
		if (!(aShader == NULL))
			{aShader->on();}

		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);


		if (!(aShader == NULL))
			{aShader->off();}

		glPopMatrix();



		// Render shadow
		glPushMatrix();
		const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
		glMultMatrixf(shadowMat);
		glMultMatrixf(glMat);
		glDisable(GL_LIGHTING);
		glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
		//drawIE2Cylinder(0, 0, 0, 0, 0, 0, 0, float(size_t(actor->userData))*2.0f);
		drawCube(0, 0, 0, float(size_t(actor->userData))*2.0f);

		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	*/
}