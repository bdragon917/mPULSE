#include "RenderingEngine.h"


RenderingEngine::RenderingEngine()
{
    showConsole = true;
    zRot = 0.0f;
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
	setUpPerpView();
	createLight();
	initializeGL();

    debugPhysX = false;
    showScene = true;
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
void RenderingEngine::prints(float inX, float inY, string s)
{
    glRasterPos3f(0.0f ,0.0f , 0.0f);
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

    float x = 10 + inX;
    float y = SCREEN_HEIGHT - 20 + inY;
    glTranslatef(x*10.0f, y*10.0f, 0.0f);
    //glRasterPos2i(10,10);     //not important i guess??


     for (unsigned int i=0; i < s.size(); i++)
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


void RenderingEngine::drawGroundPlane()
{    //*
	//Draws a checkboard Ground

    int size = 200;  //size of the ground, or at least half of the length of the plane

	 for (int x = -size;x<size;x=x+2)
         for (int y = -size;y<size;y=y+2)
            drawCheckerBoard(x,y);
     //*/
}

void RenderingEngine::drawCheckerBoard(float x, float y)
{    //*
	//Draws a checkboard Ground
    float gz = 0.0f;

	 glBegin(GL_QUADS);	
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x-1.0,gz,y+-1.0);
		glVertex3f(x+0.0,gz,y+-1.0);
		glVertex3f(x+0.0,gz,y+0.0);
		glVertex3f(x+-1.0,gz,y+0.0);

		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(x+0.0,gz,y+-1.0);
		glVertex3f(x+1.0,gz,y+-1.0);
		glVertex3f(x+1.0,gz,y+0.0);
		glVertex3f(x+0.0,gz,y+0.0);

		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(x+-1.0,gz,y+0.0);
		glVertex3f(x+0.0,gz,y+0.0);
		glVertex3f(x+0.0,gz,y+1.0);
		glVertex3f(x+-1.0,gz,y+1.0);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x+0.0,gz,y+0.0);
		glVertex3f(x+1.0,gz,y+0.0);
		glVertex3f(x+1.0,gz,y+1.0);
		glVertex3f(x+0.0,gz,y+1.0);
	 glEnd();
     //*/
}

void RenderingEngine::RenderDebugPhysic(const NxDebugRenderable* ndr)
{
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);

    int nLines = 0;
    int nTriangles = 0;
    int nPoints = 0;

    if (ndr == NULL)
    { printf("Physic DebugRenderable is NULL");}
    else
    {
        nLines =        ndr->getNbLines();
        nTriangles =    ndr->getNbTriangles();
        nPoints =       ndr->getNbPoints();
    }


    glPushMatrix();

    if (nLines)
    {
        const NxDebugLine* nxDebugLines = ndr->getLines();
        while (nLines--)
        {
            int color = nxDebugLines->color;
            float blue = color & 255;
            float green = (color >> 8) & 255;
            float red = (color >> 16) & 255;

            glBegin(GL_LINES);
            glColor3f(red, green, blue);
            //glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(nxDebugLines->p0.x, nxDebugLines->p0.y, nxDebugLines->p0.z);
            glVertex3f(nxDebugLines->p1.x, nxDebugLines->p1.y, nxDebugLines->p1.z);
            glEnd();
            nxDebugLines++;
        }
    }

    if (nTriangles)
    {
        const NxDebugTriangle* nxDebugTris = ndr->getTriangles();
        while (nTriangles--)
        {
            int color = nxDebugTris->color;
            float blue = color & 255;
            float green = (color >> 8) & 255;
            float red = (color >> 16) & 255;

            glBegin(GL_TRIANGLES);
            glColor3f(red, green, blue);
            glVertex3f(nxDebugTris->p0.x, nxDebugTris->p0.y, nxDebugTris->p0.z);
            glVertex3f(nxDebugTris->p1.x, nxDebugTris->p1.y, nxDebugTris->p1.z);
            glVertex3f(nxDebugTris->p2.x, nxDebugTris->p2.y, nxDebugTris->p2.z);
            glEnd();
            nxDebugTris++;
        }
    }

    if (nPoints)
    {
        const NxDebugPoint* nxDebugPts = ndr->getPoints();
        while (nLines--)
        {
            int color = nxDebugPts->color;
            float blue = color & 255;
            float green = (color >> 8) & 255;
            float red = (color >> 16) & 255;

            glBegin(GL_LINE);
            glColor3f(red, green, blue);
            glVertex3f(nxDebugPts->p.x, nxDebugPts->p.y, nxDebugPts->p.z);
            glEnd();
            nxDebugPts++;
        }
    }

    glPopMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
}

void RenderingEngine::displayConsole()
{

    	 glColor3f(1.0f,1.0f,1.0f);

     prints(0,  0,      aConsole.consoleOut[5]);
     prints(0,  -20,    aConsole.consoleOut[4]);
     prints(0,  -40,    aConsole.consoleOut[3]);
     prints(0,  -60,    aConsole.consoleOut[2]);
     prints(0,  -80,    aConsole.consoleOut[1]);
     prints(0,  -100,   aConsole.consoleOut[0]);
     prints(0,  -140,   aConsole.consoleString);
     //prints(0,  -200,   debugOut);

}



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

    int err = glewInit();               //Needs a window to execute successfully
	
   if (err == GLEW_OK)
		{printf("glewInit is successful!\n");aShader = new Shader("shaders/texture.frag", "shaders/texture.vert");}
    else
    {fprintf(stderr, "Error: %s\n", glewGetErrorString(err));//printf("%i\n",err);
    }
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

void RenderingEngine::drawScene(NxScene* scene, Entities* entities)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();
	glLoadIdentity ();
	
    entities->cars.at(0)->aCam->updateCamera();

    NxVec3 pos = entities->cars.at(0)->aCam->getCamLoc();
    NxVec3 at = entities->cars.at(0)->aCam->getLookAt();

	//Cameras
	gluLookAt(pos.x, pos.y, pos.z,  // Eye/camera position
	at.x ,at.y,at.z,		// Look-at position 

  //  	gluLookAt(0, 0, 0,  // Eye/camera position
	//0 ,0,-2.0f,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	
	//set view
	setUpPerpView();
	//glRotatef (10.0f, 10.0f, 0.0, 0.0);
	
    if (showScene)
    {
	    glColor3f(0.75f, 0.75f, 0.75f);
	    //Draws a checkboard Ground
	     drawGroundPlane();
         glColor3f(1.0f, 1.0f, 1.0f);

         char shaded = 'f';

         if (aShader != NULL)
         {
            aShader->on();
            shaded = 't';
         }

		// Render all actors
	    int nbActors = scene->getNbActors();
	    NxActor** actors = scene->getActors();
	    while(nbActors--)
	    {
		    NxActor* actor = *actors++;
			drawActor(actor);
        }
    }

     if (aShader != NULL)
        aShader->off();

     if (debugPhysX) //If debugPhyX then
          RenderDebugPhysic(scene->getDebugRenderable());

    if (showConsole)
        displayConsole();


	glEnable(GL_LIGHTING);
	glPopMatrix();
}


void RenderingEngine::drawActor(NxActor* actor)
{
	NxShape* const* shapes = actor->getShapes();
	NxU32 nShapes = actor->getNbShapes();

	while(nShapes--)
	{
		drawShape(shapes[nShapes]);
	}
}


void RenderingEngine::drawShape(NxShape* shape)
{
	int type = shape-> getType();

	switch(type)
	{
	case(NX_SHAPE_BOX):
		drawBox(shape->isBox());
		break;
	}
}


void RenderingEngine::drawBox(NxBoxShape* box)
{
	NxMat34 pose = box->getGlobalPose();
	float mat[16];

	pose.getColumnMajor44(mat);

	NxVec3 boxDim = box->getDimensions();

	glPushMatrix();

		glMultMatrixf(mat);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		
		// (boxDim.x ) (boxDim.y ) (boxDim.z )

		glBegin(GL_POLYGON);
		//Bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( (boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f( (boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,1.0); glVertex3f(-(boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glTexCoord2d(0.0,1.0); glVertex3f(-(boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		glEnd();

		glBegin(GL_POLYGON);
		//Left
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(-(boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f(-(boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,1.0); glVertex3f(-(boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,1.0); glVertex3f(-(boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		//glVertex3f(-d, -d, -d);
		glEnd();

		glBegin(GL_POLYGON);
		//Right
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( (boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f( (boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,1.0); glVertex3f( (boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glTexCoord2d(0.0,1.0); glVertex3f( (boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glEnd();

		glBegin(GL_POLYGON);
		//Front
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(-(boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f( (boxDim.x ), -(boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,1.0) ;glVertex3f( (boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glTexCoord2d(0.0,1.0); glVertex3f(-(boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glEnd();

		glBegin(GL_POLYGON);
		//Back
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( (boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f( (boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,1.0) ;glVertex3f(-(boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glTexCoord2d(0.0,1.0); glVertex3f(-(boxDim.x ), -(boxDim.y ),  (boxDim.z ));
		glEnd();

		glBegin(GL_POLYGON);
		//Top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f( (boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glTexCoord2d(1.0,0.0); glVertex3f( (boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glTexCoord2d(1.0,1.0); glVertex3f(-(boxDim.x ),  (boxDim.y ), -(boxDim.z ));
		glTexCoord2d(0.0,1.0); glVertex3f(-(boxDim.x ),  (boxDim.y ),  (boxDim.z ));
		glEnd();

		//

	glPopMatrix();
}

int RenderingEngine::drawIntro()
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

////Draw Functions
//
//void RenderingEngine::drawCube(float x, float y, float z, float size)
//{
//	glPushMatrix();	
//	glTranslatef(	x, y, z);	
//	
//	float d = size / 2;
//
//		glBegin(GL_POLYGON);
//		//Bottom
//		glNormal3f(0.0f, -1.0f, 0.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f( d, -d, -d);
//		glTexCoord2d(1.0,0.0); glVertex3f( d, -d,  d);
//		glTexCoord2d(1.0,1.0); glVertex3f(-d, -d,  d);
//		glTexCoord2d(0.0,1.0); glVertex3f(-d, -d, -d);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//				//Left
//		glNormal3f(1.0f, 0.0f, 0.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f(-d, -d,  d);
//		glTexCoord2d(1.0,0.0); glVertex3f(-d,  d,  d);
//		glTexCoord2d(1.0,1.0); glVertex3f(-d,  d, -d);
//		glVertex3f(-d, -d, -d);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//				//Right
//		glNormal3f(-1.0f, 0.0f, 0.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f( d, -d, -d);
//		glTexCoord2d(1.0,0.0); glVertex3f( d,  d, -d);
//		glTexCoord2d(1.0,1.0); glVertex3f( d,  d,  d);
//		glTexCoord2d(0.0,1.0); glVertex3f( d, -d,  d);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//				//Front
//		glNormal3f(0.0f, 0.0f, -1.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f(-d, -d, -d);
//		glTexCoord2d(1.0,0.0); glVertex3f(d, -d, -d);
//		glTexCoord2d(1.0,1.0) ;glVertex3f(d, d, -d);
//		glTexCoord2d(0.0,1.0); glVertex3f(-d, d, -d);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//				//Back
//		glNormal3f(0.0f, 0.0f, 1.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f( d, -d,  d);
//		glTexCoord2d(1.0,0.0); glVertex3f( d,  d,  d);
//		glTexCoord2d(1.0,1.0) ;glVertex3f(-d,  d,  d);
//		glTexCoord2d(0.0,1.0); glVertex3f(-d, -d,  d);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//				//Top
//		glNormal3f(0.0f, 1.0f, 0.0f);
//		glTexCoord2d(0.0,0.0); glVertex3f( d,  d,  d);
//		glTexCoord2d(1.0,0.0); glVertex3f( d,  d, -d);
//		glTexCoord2d(1.0,1.0); glVertex3f(-d,  d, -d);
//		glTexCoord2d(0.0,1.0); glVertex3f(-d,  d,  d);
//		glEnd();
//	
//	glPopMatrix();
//
//}
///

//int RenderingEngine::drawIntro(){
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
//	glFlush();
//
//	glPopMatrix();
//
//	return 1;
//
//}