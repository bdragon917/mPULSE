#include "RenderingEngine.h"

RenderingEngine::RenderingEngine()
{
    modelManager.loadModelsFromList(modelManager.MODEL_LIST_FILENAME);
    showConsole = true;
    zRot = 0.0f;
    SCREEN_WIDTH = 1024;
    SCREEN_HEIGHT = 768;
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


ModelManager RenderingEngine::getModelManger()
{
    return modelManager;
}


//Texture Stuff
void RenderingEngine::bindBMPtoTexture(char* filename, GLuint textures)
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

	//glGenTextures(1, &textures);

	glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
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

    textureid_P1 = new GLuint[8];
    glGenTextures(8, textureid_P1);

    bindBMPtoTexture("./img/testT.bmp", textureid_P1[0]);
    bindBMPtoTexture("./img/loadScreen.bmp", textureid_P1[1]);
    bindBMPtoTexture("./img/hello.bmp", textureid_P1[2]);
    bindBMPtoTexture("./img/Saruk.bmp", textureid_P1[3]);
    bindBMPtoTexture("./img/Box.bmp", textureid_P1[4]);
    bindBMPtoTexture("./img/Box2.bmp", textureid_P1[5]);
    bindBMPtoTexture("./img/Box3.bmp", textureid_P1[6]);
    bindBMPtoTexture("./img/white.bmp", textureid_P1[7]);
	//"/img/textureTest.bmp"

	//int err = aBMPImg.Load("./img/testT.bmp");
	//if (!(err == 1))
	//{printf("Error: Loading Texture: %i\n", err);}
	//data = aBMPImg.GetImg();
	//width = aBMPImg.GetWidth();
	//height = aBMPImg.GetHeight();
	////aBMPImg.GetImg
	////LoadPicture(data);

	////glEnable (GL_TEXTURE_2D);		//Don't need this, since shader programs will control texture usage
	//glGenTextures(1, &textureid_P1);

	//glBindTexture(GL_TEXTURE_2D, textureid_P1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
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

void RenderingEngine::drawModel(ObjModel* model,int x,int y, int z, int scale)
{
    std::vector<std::vector<ObjModel::vertElements>>* faces = model->getFaces();
    std::vector<ObjModel::vertex3d>* verticies = model->getVerticies();
    std::vector<ObjModel::vertex3d>* norms = model->getVertexNormals();
    std::vector<ObjModel::vertex2d>* texs = model->getVertexTextureCoords();

    ObjModel::vertElements face;
    ObjModel::vertex3d  vert;
    ObjModel::vertex3d  norm;
    ObjModel::vertex2d  tex;

    glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<faces->size();i++)
    {
        for(int j=0;j<faces->at(i).size();j++)
        {            
            face = faces->at(i).at(j);
            vert = verticies->at(face.vertIndex);

            if(model->getNormalsEnabled())            
            {
                norm = norms->at(face.vertNormalIndex);
                glNormal3f(norm.x,norm.y,norm.z);
            }
            if(model->getTextureCoordsEnabled())
            {
                tex = texs->at(face.vertTextureIndex);
                glTexCoord2d(tex.x,tex.y);
            }

            glVertex3f(x+(vert.x*scale),y+(vert.y*scale),z+(vert.z*scale));
        }
    }
    glEnd();
}


void RenderingEngine::drawModelPos(ObjModel* model, NxMat34* aPose)
{
    glPushMatrix();

 	float mat[16];
	aPose->getColumnMajor44(mat);
    
    glMultMatrixf(mat);
    std::vector<std::vector<ObjModel::vertElements>>* faces = model->getFaces();
    std::vector<ObjModel::vertex3d>* verticies = model->getVerticies();
    std::vector<ObjModel::vertex3d>* norms = model->getVertexNormals();
    std::vector<ObjModel::vertex2d>* texs = model->getVertexTextureCoords();

    ObjModel::vertElements face;
    ObjModel::vertex3d  vert;
    ObjModel::vertex3d  norm;
    ObjModel::vertex2d  tex;

    glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<faces->size();i++)
    {
        for(int j=0;j<faces->at(i).size();j++)
        {            
            face = faces->at(i).at(j);
            vert = verticies->at(face.vertIndex);

            if(model->getNormalsEnabled())            
            {
                norm = norms->at(face.vertNormalIndex);
                glNormal3f(norm.x,norm.y,norm.z);
            }
            if(model->getTextureCoordsEnabled())
            {
                tex = texs->at(face.vertTextureIndex);
                glTexCoord2d(tex.x,tex.y);
            }

            glVertex3f((vert.x),(vert.y),(vert.z));
        }
    }
    glEnd();

    glPopMatrix();
}

void RenderingEngine::drawModelShadow(ObjModel* model, NxMat34* aPose)
{
    glPushMatrix();

 	float mat[16];
	aPose->getColumnMajor44(mat);
    glDisable(GL_TEXTURE_2D);
	const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
	glMultMatrixf(shadowMat);
    glMultMatrixf(mat);
    std::vector<std::vector<ObjModel::vertElements>>* faces = model->getFaces();
    std::vector<ObjModel::vertex3d>* verticies = model->getVerticies();
    std::vector<ObjModel::vertex3d>* norms = model->getVertexNormals();
    std::vector<ObjModel::vertex2d>* texs = model->getVertexTextureCoords();

    ObjModel::vertElements face;
    ObjModel::vertex3d  vert;
    ObjModel::vertex3d  norm;
    ObjModel::vertex2d  tex;

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);      //Shadow

    glBegin(GL_TRIANGLES);
    for(int i=0;i<faces->size();i++)
    {
        for(int j=0;j<faces->at(i).size();j++)
        {            
            face = faces->at(i).at(j);
            vert = verticies->at(face.vertIndex);

            if(model->getNormalsEnabled())            
            {
                norm = norms->at(face.vertNormalIndex);
                glNormal3f(norm.x,norm.y,norm.z);
            }
            if(model->getTextureCoordsEnabled())
            {
                tex = texs->at(face.vertTextureIndex);
                glTexCoord2d(tex.x,tex.y);
            }

            glVertex3f((vert.x),(vert.y),(vert.z));
        }
    }
    glEnd();


    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
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


void RenderingEngine::drawGroundPlane(float xoffset, float yoffset)
{    //*
	//Draws a checkboard Ground
    int size = 200;
    glBegin(GL_QUADS);	
    glTexCoord2d(-1,-1);    glNormal3d(0,1,0);      glVertex3f(-1*size,0,-1*size);
    glTexCoord2d(-1, 1);    glNormal3d(0,1,0);      glVertex3f(-1*size,0,size);
    glTexCoord2d(1, 1);     glNormal3d(0,1,0);      glVertex3f(size,0,size);
    glTexCoord2d(1,-1);     glNormal3d(0,1,0);      glVertex3f(size,0,-1*size);
    glEnd();

    /*int size = 50;  //size of the ground, or at least half of the length of the plane

	 for (int x = -size  ;x<size;x=x+2)
         for (int y = -size ;y<size;y=y+2)
            drawCheckerBoard(x + xoffset,y + yoffset);
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
	

    //Infinite Plane!
    int groundxoffset = (int(entities->cars.at(0)->getActor()->getGlobalPose().t.x));//(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.x) - (int(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.x));
    int groundyoffset = (int(entities->cars.at(0)->getActor()->getGlobalPose().t.z));//(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.z) - );

    float gxo = groundxoffset;
    float gyo = groundyoffset;

    if ((groundxoffset % 2) == 0)
    {gxo = (groundxoffset) - 1.0f;}
    if ((groundyoffset % 2) == 0)
    {gyo = (groundyoffset) - 1.0f;}

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

         char shaded = 'f';

         if (aShader != NULL)
         {
            glEnable(GL_TEXTURE_2D);
            aShader->on();
            shaded = 't';
         }

                // glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
                 //drawGroundPlane(gxo, gyo);
                 glBindTexture(GL_TEXTURE_2D, textureid_P1[7]);
                 //drawModel(modelManager.getModel(2),0,0,0,1);           //the track

                 //glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
                 //for(int i=0;i<modelManager.numOfModels;i++)
                 //drawModel(modelManager.getModel(i),0,10,0,1);


//                glBindTexture(GL_TEXTURE_2D, textureid_P1[3]);
//                NxMat34* aPose = &(entities->cars[0]->getActor()->getGlobalPose());
                //drawModelPos(modelManager.getModel(1), aPose );

                //Shadow
                 if (aShader != NULL)
                 {
                    aShader->off();
                 }
                glPushMatrix();

		        //drawModelShadow(modelManager.getModel(1), aPose );

		        glPopMatrix();
                if (aShader != NULL)
                 {
                    aShader->on();
                 }


                 //Map
                 if (aShader != NULL)
                 {
                    aShader->off();
                 }
                glPushMatrix();
                 	glDisable(GL_TEXTURE_2D);
	                //const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
                    const static float mapMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
                    const NxVec3 v(1,0,0);  //Rotate the map
                    const NxReal ang = 90;

                    NxQuat q;
                    q.fromAngleAxis(ang,v);
                    NxMat33 o;
                    o.fromQuat(q);
                    const static float rotMat[]={ o.getRow(0).x,o.getRow(0).y,o.getRow(0).z,0,
                                                    o.getRow(1).x,o.getRow(1).y,o.getRow(1).z,0,
                                                    o.getRow(2).x,o.getRow(2).y,o.getRow(2).z,0,
                                                    o.getRow(3).x,o.getRow(3).y,o.getRow(3).z,1 };

	                glMultMatrixf(mapMat);
//                    glMultMatrixf(rotMat);
	                
                       glColor3f(1.0f,1.0f,1.0f);
 //                      drawCars(entities);
   //                    drawAICars(entities);
     //                  drawTrack(entities);

                    glEnable(GL_TEXTURE_2D);
		        glPopMatrix();
                if (aShader != NULL)
                 {
                    aShader->on();
                 }




            drawCars(entities);
            //drawAICars(entities);
            drawObstacles(entities);
            //drawStaticObjs(entities);
            drawTrack(entities);


            {
               
            }
            /**
           // glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
           // for(int i=0;i<modelManager.numOfModels;i++)
           //     drawModel(modelManager.getModel(i),0,10,0,1);

            glBindTexture(GL_TEXTURE_2D, textureid_P1[3]);
            drawModel(modelManager.getModel(1),0,10,0,1);

            */
		    // Render all actors
	        int nbActors = scene->getNbActors();
	        NxActor** actors = scene->getActors();
	        while(nbActors--)
	        {
		        NxActor* actor = *actors++;
			    //drawActor(actor);
            }
            //*/
    }



     if (aShader != NULL)
        aShader->off();


     if (debugPhysX) //If debugPhyX then
          RenderDebugPhysic(scene->getDebugRenderable());


     glDisable(GL_TEXTURE_2D);
    if (showConsole)
        displayConsole();


	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void RenderingEngine::drawCars(Entities* entities)
{
if (entities->cars.size() > 0)
            for (int i=0;i <= entities->cars.size()-1;i++)      //Should be =<
            {

                if (entities->cars[i]->rc.size() > 0)
                {
                 for (int r=0;r <= entities->cars[i]->rc.size()-1;r++)
                    {
                        glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->cars[i]->rc[r]->textureID]);
                        NxMat34* aPose = &(entities->cars[i]->getActor()->getGlobalPose());
                        //drawModel(modelManager.getModel(entities->cars[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
                        drawModelPos(modelManager.getModel(entities->cars[i]->rc[r]->modelID), aPose );
                    }
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                    drawActor(entities->cars[i]->getActor());
                }
            }
}

void RenderingEngine::drawAICars(Entities* entities)
{
if (entities->AIcars.size() > 0)
            for (int i=0;i <= entities->AIcars.size()-1;i++)
            {
            if (entities->AIcars[i]->rc.size() > 0)
                {
                    for (int r=0;r <= entities->AIcars[i]->rc.size()-1;r++)
                    {
                        glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->AIcars[i]->rc[r]->textureID]);
                        NxMat34* aPose = &(entities->AIcars[i]->getActor()->getGlobalPose());
                        //drawModel(modelManager.getModel(entities->AIcars[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
                        drawModelPos(modelManager.getModel(entities->AIcars[i]->rc[r]->modelID), aPose );
                    }
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                    drawActor(entities->AIcars[i]->getActor());
                }
            }
}

void RenderingEngine::drawObstacles(Entities* entities)
{
            if (entities->Obstacles.size() > 0)
            for (int i=0;i <= entities->Obstacles.size()-1;i++)
            {
                if (entities->Obstacles[i]->rc.size() > 0)
                {
                    for (int r=0;r <= entities->Obstacles[i]->rc.size()-1;r++)
                    {
                        glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->Obstacles[i]->rc[r]->textureID]);
                        int s = entities->Obstacles[i]->rc.size();  //debug
                        NxMat34* aPose = &(entities->Obstacles[i]->getActor()->getGlobalPose());
                        drawModelPos(modelManager.getModel(entities->Obstacles[i]->rc[r]->modelID), aPose );
                    }
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[4]);
                    if (entities->Obstacles[i]->getActor() == NULL)
                    {printf("Obstacles has no actors\n");}
                    else
                    {
//                        drawActor_Safe(entities->Obstacles[i]->getActor());
                        //drawActor(entities->Obstacles[i]->getActor());
                    }
                }
            }
}

void RenderingEngine::drawStaticObjs(Entities* entities)
{
if (entities->StaticObjs.size() > 0)
             for (int i=0;i <= entities->StaticObjs.size()-1;i++)
            {
                if (entities->StaticObjs[i]->rc.size() > 0)
                {
                    for (int r=0;r <= entities->StaticObjs[i]->rc.size()-1;r++)
                    {
                        glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->StaticObjs[i]->rc[r]->textureID]);
                        int s = entities->StaticObjs[i]->rc.size();  //debug
                        NxMat34* aPose = &(entities->StaticObjs[i]->getActor()->getGlobalPose());
                        drawModelPos(modelManager.getModel(entities->StaticObjs[i]->rc[r]->modelID), aPose );
                    }
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[5]);
                     if (entities->StaticObjs[i]->rc.size() > 0)
                    {printf("StaticObj has no actors\n");}
                    else
                    {
 //                        drawActor_Safe(entities->StaticObjs[i]->getActor());
//                        drawActor(entities->StaticObjs[i]->getActor());///BUGGY
                     }
                }
            }
}

void RenderingEngine::drawTrack(Entities* entities)
{
if (entities->Track.size() > 0)
            for (int i=0;i <= entities->Track.size()-1;i++)
            {
                if (entities->Track[i]->rc.size() > 0)
                {
                    for (int r=0;r <= entities->Track[i]->rc.size()-1;r++)
                    {
                        glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->Track[i]->rc[r]->textureID]);
                        NxMat34* aPose = &(entities->Track[i]->getActor()->getGlobalPose());
                        //drawModel(modelManager.getModel(entities->Track[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
                        drawModelPos(modelManager.getModel(entities->Track[i]->rc[r]->modelID), aPose );
                    }
                }
                else
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                    if (entities->Track[i]->getActor() == NULL)
                    {printf("Track has no actors\n");}
                    else
                    {
 //                   drawActor(entities->Track[i]->getActor());///BUGGY
                    }
                }
            }
}


void RenderingEngine::drawActor_Safe(NxActor* actor)
{
    glPushMatrix();
    NxMat34 aPose = actor->getGlobalPose();
 	float mat[16];
	aPose.getColumnMajor44(mat);
    
    glMultMatrixf(mat);

    drawBox_Generic(1.0f);


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


void RenderingEngine::drawBox_Generic(float size)
{

	NxVec3 boxDim = NxVec3(size,size,size);

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