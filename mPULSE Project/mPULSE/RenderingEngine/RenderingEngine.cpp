#include <RenderingEngine/RenderingEngine.h>

RenderingEngine::RenderingEngine()
{
    modelManager.loadModelsFromList(modelManager.MODEL_LIST_FILENAME);
    string modelManageErr = modelManager.getErrorMessage();
    cout << "modelManger: " << modelManageErr << "\n";

    showConsole = true;
    zRot = 0.0f;
    SCREEN_WIDTH = 1024;
    SCREEN_HEIGHT = 768;
	setUpPerpView();
	createLight();
	initializeGL();

    FadeCtrl = 1.0f;
    fadeMode = 1;

    debugPhysX = false;
    showScene = true;
    debugCamera = false;
}

RenderingEngine* RenderingEngine::getInstance()
{
    static RenderingEngine renderer;
    return &renderer;
}

GLuint RenderingEngine::generateDisplayList(std::string modelName,int x,int y,int z,int scale)
{
    ObjModel* model = modelManager.getModel(modelName);
    GLuint index = -1;
    if(model != NULL)
    {
        index = glGenLists(1);
        if(index != 0)
        {
            glNewList(index, GL_COMPILE);
            drawModel(model,x,y,z,scale);
            glEndList();
            displayLists.push_back(index);
        }
    }
    return index;
}

GLuint RenderingEngine::generateDisplayList(ObjModel* model,int x,int y,int z,int scale)
{
    GLuint index = -1;
    if(model != NULL)
    {
        index = glGenLists(1);
        if(index != 0)
        {
            glNewList(index, GL_COMPILE);
            drawModel(model,x,y,z,scale);
            glEndList();
            displayLists.push_back(index);
        }
    }
    return index;
}

void RenderingEngine::deleteDisplayList(GLuint index)
{
    glDeleteLists(index,1);
}

void RenderingEngine::drawDisplayList(int index)
{
    glCallList(index);
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
	{printf("Error: Loading Texture: %i %s\n", err, filename);}
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

    textureid_P1 = new GLuint[37];
    glGenTextures(37, textureid_P1);

    bindBMPtoTexture("./Images/testT.bmp", textureid_P1[0]);
    bindBMPtoTexture("./Images/loadScreen.bmp", textureid_P1[1]);
    bindBMPtoTexture("./Images/hello.bmp", textureid_P1[2]);
    bindBMPtoTexture("./Images/Saruk.bmp", textureid_P1[3]);
    bindBMPtoTexture("./Images/Box.bmp", textureid_P1[4]);
    bindBMPtoTexture("./Images/Box2.bmp", textureid_P1[5]);
    bindBMPtoTexture("./Images/Box3.bmp", textureid_P1[6]);
    bindBMPtoTexture("./Images/white.bmp", textureid_P1[7]);
    bindBMPtoTexture("./Images/Menu/MenuBG2.bmp", textureid_P1[8]);
    bindBMPtoTexture("./Images/Menu/single.bmp", textureid_P1[9]);
    bindBMPtoTexture("./Images/Menu/singleS.bmp", textureid_P1[10]);
    bindBMPtoTexture("./Images/Menu/versus.bmp", textureid_P1[11]);
    bindBMPtoTexture("./Images/Menu/versusS.bmp", textureid_P1[12]);
    bindBMPtoTexture("./Images/Menu/story.bmp", textureid_P1[13]);
    bindBMPtoTexture("./Images/Menu/storyS.bmp", textureid_P1[14]);
    bindBMPtoTexture("./Images/Menu/setting.bmp", textureid_P1[15]);
    bindBMPtoTexture("./Images/Menu/settingS.bmp", textureid_P1[16]);
    bindBMPtoTexture("./Images/Menu/quit.bmp", textureid_P1[17]);
    bindBMPtoTexture("./Images/Menu/quitS.bmp", textureid_P1[18]);

    bindBMPtoTexture("./Images/HUD.bmp", textureid_P1[19]);

    //Skybox texture
    bindBMPtoTexture("./Images/sb/ss_front5.bmp", textureid_P1[20]);
    bindBMPtoTexture("./Images/sb/ss_back6.bmp", textureid_P1[21]);
    bindBMPtoTexture("./Images/sb/ss_left2.bmp", textureid_P1[22]);
    bindBMPtoTexture("./Images/sb/ss_right1.bmp", textureid_P1[23]);
    bindBMPtoTexture("./Images/sb/ss_top3.bmp", textureid_P1[24]);
    bindBMPtoTexture("./Images/sb/ss_bottom4.bmp", textureid_P1[25]);

    bindBMPtoTexture("./Images/WIN.bmp", textureid_P1[26]);

    bindBMPtoTexture("./Images/motherShipHullUV.bmp", textureid_P1[27]);
    bindBMPtoTexture("./Images/motherShipEngineUV.bmp", textureid_P1[28]);

    bindBMPtoTexture("./Images/SpdNumber.bmp", textureid_P1[29]);


    /////
    bindBMPtoTexture("./Images/outUVBarrierDisc.bmp", textureid_P1[30]);
    bindBMPtoTexture("./Images/outUVBarrierScreen.bmp", textureid_P1[31]);
    bindBMPtoTexture("./Images/outUVMissile.bmp", textureid_P1[32]);

    bindBMPtoTexture("./Images/Menu/Profiles/LoadProfile.bmp", textureid_P1[33]);

    bindBMPtoTexture("./Images/FontTexture.bmp", textureid_P1[34]);
    bindBMPtoTexture("./Images/FontSelectedTexture.bmp", textureid_P1[35]);
    bindBMPtoTexture("./Images/FontTitleTexture.bmp", textureid_P1[36]);


	//"/Images/textureTest.bmp"

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


	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // the texture wraps over at the edges (repeat)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
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
    //Sanity Check
    if (model == NULL)
    {MessageBox(NULL, "Accessing invalid model....Did we loaded the models? Did we downloaded models....", NULL, NULL);}

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
    for (unsigned i = 0; i < faces->size(); ++i)
    {
        for (unsigned j = 0; j < faces->at(i).size(); ++j)
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
    for (unsigned i = 0; i < faces->size(); ++i)
    {
        for (unsigned j = 0; j < faces->at(i).size(); ++j)
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
    for (unsigned i = 0; i < faces->size(); ++i)
    {
        for (unsigned j = 0; j < faces->at(i).size(); ++j)
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



void RenderingEngine::renderText(float startX, float startY, float fontHeight, float FontWidth, int fontTexture, string str, bool invert)
{
    glBindTexture(GL_TEXTURE_2D, textureid_P1[fontTexture]);

    float curXOffset = 0;

    //Select Correct UV coordinates, draw a square with that coordiate, inc location
    for (unsigned i = 0; i < str.size(); i++)
    {
        char c = str[i];

        const float border = 1/ 256.0f;

        float y = 1.0f - (((c / 16) + 1) / 16.0f);
        float x = (c % 16) / 16.0f + border;
        const float gridSpacing = (1.0f / 16.0f) - border;    //size of cell

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        if (invert)
        {
		    glTexCoord2d(x,y);                              glVertex3f(   (startX)       + curXOffset,          (startY+fontHeight),    (0)   );        //upperleft
		    glTexCoord2d(x,y+gridSpacing);                  glVertex3f(   (startX)       + curXOffset,          (startY),               (0)   );        //lowerleft
		    glTexCoord2d(x+gridSpacing,y+gridSpacing);      glVertex3f(   (startX+FontWidth) + curXOffset,      (startY),               (0)   );        //lowerright
		    glTexCoord2d(x+gridSpacing,y);                  glVertex3f(   (startX+FontWidth) + curXOffset,      (startY+fontHeight),    (0)   );        //upperright
        }
        else
        {
		    glTexCoord2d(x,y);                              glVertex3f(   (startX)       + curXOffset,          (startY),               (0)   );        //lowerleft
		    glTexCoord2d(x,y+gridSpacing);                  glVertex3f(   (startX)       + curXOffset,          (startY+fontHeight),    (0)   );        //upperleft
		    glTexCoord2d(x+gridSpacing,y+gridSpacing);      glVertex3f(   (startX+FontWidth) + curXOffset,      (startY+fontHeight),    (0)   );        //upperright
		    glTexCoord2d(x+gridSpacing,y);                  glVertex3f(   (startX+FontWidth) + curXOffset,      (startY),               (0)   );        //lowerright
        }
        glEnd();

        curXOffset = curXOffset + FontWidth;
    }


}

/**
*	This draws a string on screen
**/
void RenderingEngine::drawText(float inX, float inY, string s)
{
    drawableText t;
    t.text = s;
    t.x = inX;
    t.y = inY;

    textQueue.push_back(t);

}

void RenderingEngine::drawAllText()
{
    
    glRasterPos3f(0.0f ,0.0f , 0.0f);
    glDisable(GL_LIGHTING);

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    for(unsigned i=0;i<textQueue.size();i++)
    {
        drawableText words = textQueue[i];
        float x = 10 + words.x;
        float y = SCREEN_HEIGHT - 20 + words.y;

        glScalef(0.1, 0.1, 0.1);
        glTranslatef(x*10.0f, y*10.0f, 0.0f);

        for (unsigned int ch=0; ch < words.text.size(); ch++)
        {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, words.text[ch]);
        }
        glLoadIdentity();
    }

    textQueue.clear();

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

     glEnable(GL_LIGHTING);
}

void RenderingEngine::drawHUD(NxActor* carActor, bool hasWon)
{
    aHUDShader->on();

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(70, 1, 1, 100);
    setPerspective( 70, 1, 1, 100, 1.0f, 1.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);


    /*
    glBindTexture(GL_TEXTURE_2D, textureid_P1[19]);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(1.0f, -0.5f);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(-1.0f, -0.5f);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(-1.0f, -1.0f);
    glEnd();
    */

    //Display speed

    int curSpd = (carActor->getLinearVelocity().magnitude());
    int hundreds = (curSpd/100);
    int tens = (curSpd-(hundreds*100)) /10;
    int ones = (curSpd-((hundreds*100)+(tens*10)));
    int tenth = ((carActor->getLinearVelocity().magnitude()*10)-((hundreds*1000)+(tens*100)+(ones*10)));

    drawText(850,-600, "Spd: " + FloatToString(hundreds) + " " + FloatToString(tens) + " " + FloatToString(ones));


    //one
    //0.1f assumes there is ten characters
    float displaceTenths = 0.1f * tenth;

    glBindTexture(GL_TEXTURE_2D, textureid_P1[29]);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0);
        glTexCoord2f(displaceTenths+0.1f, 0.0f);glVertex2f(0.95f, -0.90f);
        glTexCoord2f(displaceTenths+0.1f, 1.0f);glVertex2f(0.95f, -0.75f);
        glTexCoord2f(displaceTenths, 1.0f);glVertex2f(0.9f, -0.75f);
        glTexCoord2f(displaceTenths, 0.0f);glVertex2f(0.9f, -0.90f);
    glEnd();
    //one
    //0.1f assumes there is ten characters
    float displaceOnes = 0.1f * ones;

    glBindTexture(GL_TEXTURE_2D, textureid_P1[29]);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0);
        glTexCoord2f(displaceOnes+0.1f, 0.0f);glVertex2f(0.9f, -0.90f);
        glTexCoord2f(displaceOnes+0.1f, 1.0f);glVertex2f(0.9f, -0.75f);
        glTexCoord2f(displaceOnes, 1.0f);glVertex2f(0.85f, -0.75f);
        glTexCoord2f(displaceOnes, 0.0f);glVertex2f(0.85f, -0.90f);
    glEnd();
    //ten

    float displaceTens = 0.1f * tens;
    glBindTexture(GL_TEXTURE_2D, textureid_P1[29]);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0);
        glTexCoord2f(displaceTens+0.1f, 0.0f);glVertex2f(0.85f, -0.90f);
        glTexCoord2f(displaceTens+0.1f, 1.0f);glVertex2f(0.85f, -0.75f);
        glTexCoord2f(displaceTens, 1.0f);glVertex2f(0.8f, -0.75f);
        glTexCoord2f(displaceTens, 0.0f);glVertex2f(0.8f, -0.90f);
    glEnd();
    //hundred
    float displaceHundred = 0.1f * hundreds;
    glBindTexture(GL_TEXTURE_2D, textureid_P1[29]);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0);
        glTexCoord2f(displaceHundred+0.1f, 0.0f);glVertex2f(0.8f, -0.90f);
        glTexCoord2f(displaceHundred+0.1f, 1.0f);glVertex2f(0.8f, -0.75f);
        glTexCoord2f(displaceHundred, 1.0f);glVertex2f(0.75f, -0.75f);
        glTexCoord2f(displaceHundred, 0.0f);glVertex2f(0.75f, -0.90);
    glEnd();


    if(hasWon)
    {
        glBindTexture(GL_TEXTURE_2D, textureid_P1[26]);
        glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0);
            glTexCoord2f(1.0f, 0.0f);glVertex2f(1.0f, -1.0f);
            glTexCoord2f(1.0f, 1.0f);glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f);glVertex2f(-1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f);glVertex2f(-1.0f, -1.0f);
        glEnd();
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


     glEnable(GL_LIGHTING);

    aHUDShader->off();

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
     
     drawText(0,  0,    aConsole.consoleOut[4]);
     drawText(0,  -20,    aConsole.consoleOut[3]);
     drawText(0,  -40,    aConsole.consoleOut[2]);
     drawText(0,  -60,    aConsole.consoleOut[1]);
     drawText(0,  -80,   aConsole.consoleOut[0]);
     drawText(0,  -120,   aConsole.consoleString);
     //drawText(0,  -200,   debugOut);

}

void RenderingEngine::setGameVariables(GameVariables* newGameVaribles)
{
    gameVariables = newGameVaribles;
}

void RenderingEngine::quickInitialize()
{
    initializeMainMenuVariables();
    
    unsigned char *data = 0;
	BMPImg aBMPImg;

    textureid_P1 = new GLuint[1];
    glGenTextures(1, textureid_P1);

    bindBMPtoTexture("./Images/loadScreen.bmp", textureid_P1[0]);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // the texture wraps over at the edges (repeat)
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );


}

void RenderingEngine::initializeGL()
{
    printf("INITAL");

    debugCam = false;


    initializeMainMenuVariables();

	glShadeModel (GL_SMOOTH);
	glEnable (GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
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


    //setPlayerNum(1);    //initalize player numbers  //Hopefully this is only called in init state
    gameVariables = GameVariables::getInstance();

    quickInitialize();

    drawLoading();
    SDL_GL_SwapBuffers();

    initializeTexture();

    

    int err = glewInit();               //Needs a window to execute successfully
	
   if (err == GLEW_OK)
		{
            printf("glewInit is successful!\n");
            aShader = new Shader("shaders/texture.frag", "shaders/texture.vert");
            aSkyBoxShader = new Shader("shaders/skybox.frag", "shaders/texture.vert");
            aShadowShader = new Shader("shaders/shadow.frag", "shaders/shadow.vert");
            aHUDShader = new Shader("shaders/BlueColorKey.frag", "shaders/BlueColorKey.vert");
			flatten = new Shader("shaders/flatten.frag", "shaders/flatten.vert");
        }
    else
    {fprintf(stderr, "Error: %s\n", glewGetErrorString(err));//printf("%i\n",err);
    }

   

   //Initalization for shadowMap
   p_camera[0] = 32;
   p_camera[1] = 20;
   p_camera[2] = 0;

    //Camera lookAt
   l_camera[0] = 2;
   l_camera[1] = 0;
   l_camera[2] = -10;

    //Light position
   p_light[0] = 3;
   p_light[1] = 20;
   p_light[2] = 0;

    //Light lookAt
   l_light[0] = 0;
   l_light[1] = 0;
   l_light[2] = -5;

    //Light mouvement circle radius
    light_mvnt = 30.0f;

    generateShadowFBO();

}

void RenderingEngine::generateShadowFBO()
{
	int shadowMapWidth = RENDER_WIDTH * SHADOW_MAP_RATIO;
	int shadowMapHeight = RENDER_HEIGHT * SHADOW_MAP_RATIO;
	
	//GLfloat borderColor[4] = {0,0,0,0};
	
	GLenum FBOstatus;
	
	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	//glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
	
	
	
	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
	
	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);
	
	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}


void RenderingEngine::setTextureMatrix(void)
{
	static double modelView[16];
	static double projection[16];
	
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5 
	// y = y* 0.5 + 0.5 
	// z = z* 0.5 + 0.5 
	// Moving from unit cube [-1,1] to [0,1]  
	const GLdouble bias[16] = {	
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0};
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();	
	glLoadMatrixd(bias);
	
	// concatating all matrice into one.
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void RenderingEngine::setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45,RENDER_WIDTH/RENDER_HEIGHT,10,40000);
    setPerspective( 45,RENDER_WIDTH/RENDER_HEIGHT,10,40000, 1.0f, 1.0f );   //equivalent to gluPerspective
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_x,position_y,position_z,lookAt_x,lookAt_y,lookAt_z,0,1,0);
}


void RenderingEngine::createLight()
{
    GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0};
	GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0,1.0,1.0,0.0};
	//GLfloat light_ambient[] = {0.0,0.0,0.0,0.1};
	//GLfloat light_diffuse[] = {0.0,0.0,0.0,1.0};
	//GLfloat light_specular[] = {0.0,0.0,0.0,1.0};
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel (GL_SMOOTH);
	
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
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

void RenderingEngine::createLight_MainMenu()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {0.0,0.0,-1.0,0.0};
	GLfloat light_ambient[] = {1.0,1.0,1.0,0.1};
	//GLfloat light_diffuse[] = {0.0,0.0,0.0,1.0};
	//GLfloat light_specular[] = {0.0,0.0,0.0,1.0};
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel (GL_SMOOTH);
		
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_position);
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
			//gluPerspective(60.0, ratio, 1.0f, 10000.0f);
            setPerspective( 60.0, ratio, 1.0f, 10000.0f, 1.0f, 1.0f );
			//glOrtho (-ratio, ratio, -1, 1, -10, 10);
	}
	else {
		// In this case the h/w ratio is > 1
		    float ratio = (float)h/(float)w;
			//gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
			//gluPerspective(60.0, ratio, 1.0/ratio, 10000.0f);
            setPerspective( 60.0, ratio, 1.0f, 10000.0f, 1.0f, 1.0f );
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

void RenderingEngine::setPerspective( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar, float xStretch, float yStretch )
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 ) * xStretch;
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;// * xStretch;


    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

void RenderingEngine::drawLoading()
{
        glPushMatrix ();
	    glLoadIdentity ();
	        //Cameras
	            gluLookAt(0, 0, -1,  // Eye/camera position      //  	gluLookAt(0, 0, 0,  // Eye/camera position
	            0,0,0,		// Look-at position                 //0 ,0,-2.0f,		// Look-at position 
	            0.0,1.0,0.0); 		// "Up" vector

	            setUpPerpView();    //setup view for one player

	            glColor3f(0.75f, 0.75f, 0.75f);          

   
                

                glDisable(GL_LIGHTING);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                //gluPerspective(70, 1, 1, 100);
                setPerspective( 70, 1, 1, 100, 1.0f, 1.0f );
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                
                glLoadIdentity();
                glOrtho(-1, 1, -1, 1, -1.0f, 1.0f);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                glPushAttrib(GL_DEPTH_TEST);
                glDisable(GL_DEPTH_TEST);

                glEnable(GL_TEXTURE_2D);

                    glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
                    glBegin(GL_QUADS);
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexCoord2f(1.0f, 0.0f);glVertex2f(1.0f, -1.0f);
                        glTexCoord2f(1.0f, 1.0f);glVertex2f(1.0f, 1.0f);
                        glTexCoord2f(0.0f, 1.0f);glVertex2f(-1.0f, 1.0f);
                        glTexCoord2f(0.0f, 0.0f);glVertex2f(-1.0f, -1.0f);
                    glEnd();

                glDisable(GL_TEXTURE_2D);
                glPopAttrib();
                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();

                
                 glEnable(GL_LIGHTING);



	    glPopMatrix();

        glDeleteTextures( 1, textureid_P1 );        //free up the LoadingScreen texture
}

//Include entity POV, which car's camera to render from
void RenderingEngine::drawScene(NxScene* scene,Track* track, Entities* entities)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gameVariables->getPlayerNum() == 2)
    {

        if (gameVariables->player2isAI)
        {
            //AI Mode
            drawScene_ForPlayer(scene, track, entities, 0, true, true, entities->cars);
            entities->AIcars.at(0)->aCam->updateCamera(16);
            drawScene_ForPlayer(scene, track, entities, 0, true, false, entities->AIcars);
        }
        else
        {
            //PlayerMode
            for (int activePlayers=0;activePlayers<2;activePlayers++)
            {
                bool isTop = false;
                if (activePlayers == 0)
                {isTop = true;}
                drawScene_ForPlayer(scene, track, entities, activePlayers, true, isTop, entities->cars);
            }
        }

    }
    else
    {
        drawScene_ForPlayer(scene, track, entities, 0, false, true, entities->cars);
    }
    //drawScene_ForPlayer(scene, entities, 1);        
}

void RenderingEngine::drawScene_ForPlayer(NxScene* scene, Track* track, Entities* entities, int carIndex, bool splitScreen, bool topScreen, std::vector<Entity*> targetEntities)
{
        glPushMatrix ();
	    glLoadIdentity ();
        

	





            
                const GLdouble bias[] = {0.5, 0.0, 0.0, 0.0, 
				    0.0, 0.5, 0.0, 0.0,
				    0.0, 0.0, 0.5, 0.0,
				    0.5, 0.5, 0.5, 1.0};

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

       // if ( bFixedFunction )
        {
	        const GLdouble x[] = {1.0, 0.0, 0.0, 0.0};
	        const GLdouble y[] = {0.0, 1.0, 0.0, 0.0};
	        const GLdouble z[] = {0.0, 0.0, 1.0, 0.0};
	        const GLdouble w[] = {0.0, 0.0, 0.0, 1.0};


	        glEnable(GL_TEXTURE_GEN_S);
	        glEnable(GL_TEXTURE_GEN_T);
	        glEnable(GL_TEXTURE_GEN_R);
	        glEnable(GL_TEXTURE_GEN_Q);

	        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	        glTexGendv(GL_S, GL_EYE_PLANE, x );
	        glTexGendv(GL_T, GL_EYE_PLANE, y );
	        glTexGendv(GL_R, GL_EYE_PLANE, z );
	        glTexGendv(GL_Q, GL_EYE_PLANE, w );
        }


	        

            NxVec3 pos = targetEntities.at(carIndex)->aCam->getCamLoc();
            NxVec3 at = targetEntities.at(carIndex)->aCam->getLookAt();
            float camXStretch = targetEntities.at(carIndex)->aCam->getXStretch();
            float camYStretch = targetEntities.at(carIndex)->aCam->getYStretch();

	        //Cameras

            if (debugCamera)
            {
                gluLookAt(0.0f, 50.0f, 0.0f,  // Eye/camera position      //  	gluLookAt(0, 0, 0,  // Eye/camera position
	            at.x ,at.y,at.z,		// Look-at position                 //0 ,0,-2.0f,		// Look-at position 
	            0.0,1.0,0.0); 		// "Up" vector
            }
            else
            {
	            gluLookAt(pos.x, pos.y, pos.z,  // Eye/camera position      //  	gluLookAt(0, 0, 0,  // Eye/camera position
	            at.x ,at.y,at.z,		// Look-at position                 //0 ,0,-2.0f,		// Look-at position 
	            0.0,1.0,0.0); 		// "Up" vector
            }

            if (splitScreen)
            {
	            //set view
                if (topScreen)
                {
            	                // Switch to the projection matrix
	                glMatrixMode (GL_PROJECTION);
	                glLoadIdentity ();

	                int w = SCREEN_WIDTH;
	                int h = SCREEN_HEIGHT / 2;

	                //int w = 640;
	                //int h = 480;

	                // Set drawing to NOT take up the entire window
	                glViewport (0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2);

	                if (w > h) {
		                // In this case the w/h ratio is > 1
		                    float ratio = (float)w/(float)h;
			                //gluPerspective(60.0, ratio, 0.01, 800.0);
			                //gluPerspective(60.0, ratio, 1.0f, 10000.0f);
                            setPerspective( 60.0, ratio, 1.0f, 10000.0f, camXStretch, 1.0f );
			                //glOrtho (-ratio, ratio, -1, 1, -10, 10);
	                }
	                else {
		                // In this case the h/w ratio is > 1
		                    float ratio = (float)h/(float)w;
			                //gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
			                //gluPerspective(60.0, ratio, 1.0/ratio, 10000.0f);
                            setPerspective( 60.0, ratio, 1.0f/ratio, 10000.0f, camXStretch, 1.0f );
			                //glOrtho (-ratio, ratio, -1, 1, -10, 10);
	                }

	                //Switch back to modelview matrix
	                glMatrixMode (GL_MODELVIEW);
                }
                else
                {
            	        // Switch to the projection matrix
	                glMatrixMode (GL_PROJECTION);
	                glLoadIdentity ();

	                int w = SCREEN_WIDTH;
	                int h = SCREEN_HEIGHT / 2;

	                //int w = 640;
	                //int h = 480;

	                // Set drawing to NOT take up the entire window
	                glViewport (0, h, w, h);

	                if (w > h) {
		                // In this case the w/h ratio is > 1
		                    float ratio = (float)w/(float)h;
			                //gluPerspective(60.0, ratio, 0.01, 800.0);
			                //gluPerspective(60.0, ratio, 1.0f, 10000.0f);
                            setPerspective( 60.0, ratio, 1.0f, 10000.0f, camXStretch, 1.0f );
			                //glOrtho (-ratio, ratio, -1, 1, -10, 10);
	                }
	                else {
		                // In this case the h/w ratio is > 1
		                    float ratio = (float)h/(float)w;
			                //gluPerspective(60.0, 1.0/ratio, 0.01, 800.0);
			                //gluPerspective(60.0, ratio, 1.0/ratio, 10000.0f);
                            setPerspective( 60.0, ratio, 1.0f/ratio, 10000.0f, camXStretch, 1.0f );
			                //glOrtho (-ratio, ratio, -1, 1, -10, 10);
	                }

	                //Switch back to modelview matrix
	                glMatrixMode (GL_MODELVIEW);
                }
            }
            else
            {
	            //setUpPerpView();    //setup view for one player
                	// Switch to the projection matrix
	                glMatrixMode (GL_PROJECTION);
	                glLoadIdentity ();

	                int w = SCREEN_WIDTH;
	                int h = SCREEN_HEIGHT;

	                glViewport (0, 0, w, h);

	                if (w > h) {
		                    float ratio = (float)w/(float)h;
                            setPerspective( 60.0, ratio, 1.0f, 10000.0f, camXStretch, 1.0f );
	                }
	                else {
		                    float ratio = (float)h/(float)w;
                            setPerspective( 60.0, ratio, 1.0f, 10000.0f, camXStretch, 1.0f );
	                }

	                //Switch back to modelview matrix
	                glMatrixMode (GL_MODELVIEW);
            }






	    //glRotatef (10.0f, 10.0f, 0.0, 0.0);


        //ShadowMap
        /**
        const GLdouble bias[] = {0.5, 0.0, 0.0, 0.0, 
				    0.0, 0.5, 0.0, 0.0,
				    0.0, 0.0, 0.5, 0.0,
				    0.5, 0.5, 0.5, 1.0};

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

       // if ( bFixedFunction )
        {
	        const GLdouble x[] = {1.0, 0.0, 0.0, 0.0};
	        const GLdouble y[] = {0.0, 1.0, 0.0, 0.0};
	        const GLdouble z[] = {0.0, 0.0, 1.0, 0.0};
	        const GLdouble w[] = {0.0, 0.0, 0.0, 1.0};

	        glEnable(GL_TEXTURE_GEN_S);
	        glEnable(GL_TEXTURE_GEN_T);
	        glEnable(GL_TEXTURE_GEN_R);
	        glEnable(GL_TEXTURE_GEN_Q);

	        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	        glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

	        glTexGendv(GL_S, GL_EYE_PLANE, x );
	        glTexGendv(GL_T, GL_EYE_PLANE, y );
	        glTexGendv(GL_R, GL_EYE_PLANE, z );
	        glTexGendv(GL_Q, GL_EYE_PLANE, w );
        }

        glMatrixMode(GL_TEXTURE);
        glLoadMatrixd(bias);
        glMultMatrixd(l->get_proj_matrix());
        glMultMatrixd(l->get_model_matrix());
        glMatrixMode(GL_MODELVIEW);
        **/


	
        if (showScene)
        {



            /**
            glPushMatrix();

            glEnable(GL_CULL_FACE);

            //First step: Render from the light POV to a FBO, story depth values only
	        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);	//Rendering offscreen
	
	        //Using the fixed pipeline to render to the depthbuffer
	        glUseProgramObjectARB(0);
	
	        // In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	        glViewport(0,0,RENDER_WIDTH * SHADOW_MAP_RATIO,RENDER_HEIGHT* SHADOW_MAP_RATIO);
	
	        // Clear previous frame values
	        glClear( GL_DEPTH_BUFFER_BIT);
	
	        //Disable color rendering, we only want to write to the Z-Buffer
	        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	
	        setupMatrices(p_light[0],p_light[1],p_light[2],l_light[0],l_light[1],l_light[2]);
	
	        // Culling switching, rendering only backface, this is done to avoid self-shadowing
	        glCullFace(GL_FRONT_AND_BACK);

            //aShadowShader->on();

	        //drawObjects();
            drawCars(entities);
            drawAICars(entities);
            drawObstacles(entities);
            drawStaticObjs(entities);
            drawTrack(entities);
	
	        //Save modelview/projection matrice into texture7, also add a biais
	        setTextureMatrix();
	
	
	        // Now rendering from the camera POV, using the FBO to generate shadows
	        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	
	        glViewport(0,0,RENDER_WIDTH,RENDER_HEIGHT);
	
	        //Enabling color write (previously disabled for light POV z-buffer rendering)
	        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	
	        // Clear previous frame values
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        //Using the shadow shader

	        glUseProgramObjectARB(shadowShaderId);
	        glUniform1iARB(shadowMapUniform,7);
	        glActiveTextureARB(GL_TEXTURE7);
	        glBindTexture(GL_TEXTURE_2D,depthTextureId);
            aShadowShader->on();

            drawCars(entities);
            drawAICars(entities);
            drawObstacles(entities);
            drawStaticObjs(entities);
            drawTrack(entities);


            glPopMatrix();






        	    //Cameras
	    //gluLookAt(pos.x, pos.y, pos.z,  // Eye/camera position
	    //at.x ,at.y,at.z,		// Look-at position 

      //  	gluLookAt(0, 0, 0,  // Eye/camera position
	    //0 ,0,-2.0f,		// Look-at position 
    //	0.0,1.0,0.0); 		// "Up" vector
	
	    //set view
	    //setUpPerpView();




            glDisable(GL_CULL_FACE);


            */
                  //Test comment



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
                    // glBindTexture(GL_TEXTURE_2D, textureid_P1[7]);
                     //drawModel(modelManager.getModel(2),0,0,0,1);           //the track

                     //glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
                     //for(int i=0;i<modelManager.numOfModels;i++)
                     //drawModel(modelManager.getModel(i),0,10,0,1);


    //                glBindTexture(GL_TEXTURE_2D, textureid_P1[3]);
    //                NxMat34* aPose = &(entities->cars[0]->getActor()->getGlobalPose());
                    //drawModelPos(modelManager.getModel(1), aPose );

                    /*//Shadow
                     if (aShader != NULL)
                     {
                        aShader->off();
                     }
                    glPushMatrix();

		            drawModelShadow(modelManager.getModel(1), aPose );

		            glPopMatrix();
                    if (aShader != NULL)
                     {
                        aShader->on();
                     }
                     */

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
                    //const static float rotMat[]={ o.getRow(0).x,o.getRow(0).y,o.getRow(0).z,0,
                    //                                o.getRow(1).x,o.getRow(1).y,o.getRow(1).z,0,
                    //                                o.getRow(2).x,o.getRow(2).y,o.getRow(2).z,0,
                        //                               o.getRow(3).x,o.getRow(3).y,o.getRow(3).z,1 };

                                    const static float rotMat[]={ 1,0,0,0,
                                                    0,std::cos(ang),-std::sin(ang),0,
                                                    0,std::sin(ang),std::cos(ang),0,
                                                    0,0,0,1 };

	                glMultMatrixf(mapMat);
                    //glMultMatrixf(rotMat);
	                
                        glColor3f(1.0f,1.0f,1.0f);
                        //drawCars(entities);
                        //drawAICars(entities);
                        //drawTrack(entities);

                    glEnable(GL_TEXTURE_2D);
		            glPopMatrix();


                flatten->on();
				drawShadow(entities, scene);
				flatten->off();

                    if (aShader != NULL)
                     {
                        aShader->on();
                     }


                    drawTrack(track);
                    drawDynamicObjects(&entities->DynamicObjs);
                //float blur = (entities->cars[0]->getActor()->getLinearVelocity().magnitude() / 150.0f); //blur = (blur * 0.7) + (0.3 * newblur)

                //glAccum(GL_MULT, blur);
                //glAccum(GL_ACCUM, 1 -blur );
                //glAccum(GL_RETURN, 1.0);

                drawCars(entities);



                //drawWheels(entities->cars[0], 0, 5);
                drawAICars(entities);
                drawObstacles(entities);
                drawStaticObjs(entities);



                //Draw Asteroids and debris stuff
                        //Infinite Plane!
                int groundxoffset = (int(entities->cars.at(carIndex)->getActor()->getGlobalPose().t.x));//(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.x) - (int(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.x));
                int groundyoffset = (int(entities->cars.at(carIndex)->getActor()->getGlobalPose().t.z));//(entities->cars.at(0)->components.at(0)->getActor()->getGlobalPose().t.z) - );

                float gxo = groundxoffset;
                float gyo = groundyoffset;

               // if ((groundxoffset % 2) == 0)
               // {gxo = (groundxoffset) - 1.0f;}
               // if ((groundyoffset % 2) == 0)
               // {gyo = (groundyoffset) - 1.0f;}
                if ((groundxoffset % 200) == 0)
                {gxo = (groundxoffset) - 100.0f;}
                if ((groundyoffset % 200) == 0)
                {gyo = (groundyoffset) - 100.0f;}


                //drawModel(modelManager.getModel(0), 0+gxo,0,0+gyo,1.0f);


                     //if (aShader != NULL)
                     //{
                     //   aShader->off();           //this give an interesting effect
                     //}
                    //glPushMatrix();
                    //glDisable (GL_LIGHTING);
                    aSkyBoxShader->on();
                    //glDisable (GL_COLOR_MATERIAL);
	                //glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                    //glEnable(GL_TEXTURE_2D);
                    //glDisable (GL_NORMALIZE);
                    //glDepthFunc(GL_ALWAYS);
                    drawSkyBox(0,0, 0, 10000.0f, 10000.0f, 10000.0f, 0);
                    aSkyBoxShader->off();
                    //glMaterialfv(GL_FRONT_AND_BACK,  GL_AMBIENT,  &norMat);
                    //glDepthFunc(GL_LESS);
                    //glEnable (GL_NORMALIZE);
                    //glEnable (GL_COLOR_MATERIAL);
	                //glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                    //glEnable (GL_LIGHTING);


                   //glColorMaterial(GL_FRONT_AND_BACK,  GL_AMBIENT_AND_DIFFUSE);
                   //glPopMatrix();
                //drawTrack(entities);

                        



               // if (debugCamera)
              //  {
               //     NxVec3 camLookAt = entities->cars[carIndex]->aCam->getLookAt();
              //      glPushMatrix();
              //      glTranslatef(camLookAt.x, camLookAt.y, camLookAt.z);
              //      drawBox_Generic(2.0f);
                    //drawModel(modelManager.getModel(0), camLookAt.x, camLookAt.y, camLookAt.z, 0.5f);
             //       glPopMatrix();
             //   }


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
	            //int nbActors = scene->getNbActors();
	           // NxActor** actors = scene->getActors();
	            //while(nbActors--)
	           // {
		       //     NxActor* actor = *actors++;
			        //drawActor(actor);
               // }
                //*/
        }



         if (aShader != NULL)
            aShader->off();


         if (debugPhysX) //If debugPhyX then
         {
              RenderDebugPhysic(scene->getDebugRenderable());
            drawText(800,-600, FloatToString(targetEntities[carIndex]->getActor()->getLinearVelocity().magnitude()) + ": car Spd");
            drawText(800,-620, FloatToString(targetEntities[carIndex]->getDriveWheels()->at(0)->getAxleSpeed()) + " :W0_d_Rot");
            drawText(800,-640, FloatToString(targetEntities[carIndex]->getDriveWheels()->at(1)->getAxleSpeed()) + " :W1_d_Rot");
            drawText(800,-660, FloatToString(targetEntities[carIndex]->getPassiveWheels()->at(0)->getAxleSpeed()) + " :W2_p_Rot");
            drawText(800,-680, FloatToString(targetEntities[carIndex]->getPassiveWheels()->at(1)->getAxleSpeed()) + " :W3-p_Rot");
         }


        CustomData* cd = (CustomData*)targetEntities[carIndex]->getActor()->userData;
        bool hasWon = false;

        if (cd->laps > 1)
            hasWon = true;

        
         drawHUD(targetEntities[carIndex]->getActor(), hasWon);
         //drawHUD(entities->cars[carIndex]->getActor(), hasWon);

         
         glDisable(GL_TEXTURE_2D);
        if (showConsole)
            displayConsole();

        //HUD info
        drawText(850,-700, FloatToString(entities->cars[carIndex]->getActor()->getLinearVelocity().magnitude()));
        drawText(SCREEN_WIDTH-150,-50, FloatToString(cd->laps) + " / 2 Laps");
        drawText(150,-700, FloatToString(cd->wp->id));
        

        //Ya...this should bwe put in a drawHUD element function later....

        //glPushMatrix();

    ///////////////////////////////////////////////////////////////////////////////////////////
    glDisable(GL_LIGHTING);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(70, 1, 1, 100);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    //gluLookAt(2, 2, 10, 2, 0, 0, 0, 1, 0);

    //(x,y) is from the bottom left of the window
///**
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0f, 1.0f);
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    glPushAttrib(GL_DEPTH_TEST);
//    glDisable(GL_DEPTH_TEST);

//    const static float shadowMat[]={ 1,0,0,0, 0,1,0,0, 0,0,0,0, 0,0,0,1 };
//	glMultMatrixf(shadowMat);

//    glScalef(0.1, 0.1, 0.1);

//    float inX = 400;
//    float inY = -400;

//    float x = 10 + inX;
//    float y = SCREEN_HEIGHT - 20 + inY;
//    glTranslatef(x*10.0f, y*10.0f, 0.0f);
    //glRasterPos2i(10,10);     //not important i guess??


  //  glBegin(GL_TRIANGLE_STRIP);
  //      glColor3f(1.0f,1.0f,1.0f);
  //      glVertex3f(-0.5f,0.0f,0.0f);
  //      glVertex3f(0.0f,0.5f,0.0f);
  //      glVertex3f(0.5f,0.0f,0.0f);
   // glEnd();

        switch(cd->pickupType)
        {
        case 0: //missile
            //drawModel(modelManager.getModel(4), 0, 0, 0, 0.5f);
            drawText(100,-680, "MISSILE");
            break;
        case 1:
            //drawModel(modelManager.getModel(5), 0, 0, 0, 0.5f);
            drawText(100,-680, "SHIELD");
            break;
        case 2:
            //drawModel(modelManager.getModel(6), 0, 0, 0, 0.5f);
            drawText(100,-680, "BARRIER");
            break;
        }

        //This is code to be for battery
        if (targetEntities[carIndex]->isBatteryCharged())
            drawText(200,-680, "Batt. CHARGED");
        else
            drawText(200,-680, "Batt. empty");


        drawAllText();
 //       glutStrokeCharacter(GLUT_STROKE_ROMAN, FloatToString(cd->pickupType)[0]);

 //   glPopAttrib();
 //   glMatrixMode(GL_PROJECTION);
 //   glPopMatrix();
 //   glMatrixMode(GL_MODELVIEW);
 //   glPopMatrix();
    /////////////////////////////////////////////////////////////////////////////////////////////


        glEnable(GL_LIGHTING);
	    glPopMatrix();

        /*
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
        //glPushMatrix();        ----Not sure if I need this
        glLoadIdentity();
        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);

        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(10.0, 0.0);
            glVertex2f(10.0, 10.0);
            glVertex2f(0.0, 10.0);
        glEnd();

        // Making sure we can render 3d again
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        */


        //glClear(GL_COLOR_BUFFER_BIT);

//        glPushMatrix();
                    //HUB
//        glMatrixMode(GL_MODELVIEW);
//            glBegin(GL_QUAD_STRIP);
//                glTexCoord2d(0.0,0.0);glVertex3f(-10.0f + pos.x , 10.0f  + pos.y, 0.5f  + pos.z);
//                glTexCoord2d(1.0,0.0);glVertex3f(10.0f + pos.x, 10.0f + pos.y, 0.5f + pos.z);
//                glTexCoord2d(1.0,1.0);glVertex3f(10.0 + pos.x, -10.0f + pos.y, 0.5f + pos.z);
//                glTexCoord2d(0.0,1.0);glVertex3f(-10.0f + pos.x, -10.0f + pos.y, 0.5f + pos.z);
//            glEnd();
//        glPopMatrix();



    
}


void RenderingEngine::initializeMainMenuVariables()
{
    //mainMenu initialization
    shipAngle = 40.0f;
    shipRotation = 0.1f;
    particles.clear();
}

int RenderingEngine::drawMainMenuScreen(int curMenuButton, bool clicked, float dt, ProfileScreenInfo psi)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix ();
	glLoadIdentity ();
	

    gluLookAt(0, 0, -2,  // Eye/camera position
	0 ,0, 0,		// Look-at position 
	0.0,1.0,0.0); 		// "Up" vector
	
	//set view
	setUpPerpView();
    //glEnable(GL_LIGHTING);
    //glDisable(GL_NORMALIZE);
    //glDisable(GL_TEXTURE);
	
    if (aShader != NULL)
         {
            glEnable(GL_TEXTURE_2D);
            aShader->on();
         }


    //Draw Background
    glColor4f(1.0f,1.0f,1.0f, 1.0f);
    float half_width = 1.0f * 1.54f;     //1.5f is compensation for the perpective mode
    float half_height = ((float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) * 1.54f;
    glBindTexture(GL_TEXTURE_2D, textureid_P1[8]);
    drawSquare(0, 0, 0.01f, half_width, half_height);
    
    float pad = 0.03f;
    float yLoc = -0.76f;

    glBindTexture(GL_TEXTURE_2D, textureid_P1[9]);      //image for single
    //Draw Single
    if (curMenuButton == 0)
    {glBindTexture(GL_TEXTURE_2D, textureid_P1[10]);}
    glColor4f(1.0f,1.0f,1.0f, 0.5f);
    drawSquare(1.2f, yLoc, 0, half_width * 0.175f, half_height * 0.0625f);
    glBindTexture(GL_TEXTURE_2D, textureid_P1[11]);

    //Draw Single
    if (curMenuButton == 1)
    {glBindTexture(GL_TEXTURE_2D, textureid_P1[12]);}
    glColor4f(1.0f,1.0f,1.0f, 0.5f);
    drawSquare(1.2f - ((((half_width * 0.175f) * 2) + pad) * 1.0f), yLoc, 0, half_width * 0.175f, half_height * 0.0625f);
    glBindTexture(GL_TEXTURE_2D, textureid_P1[13]);

    //Draw Single
    if (curMenuButton == 2)
    {glBindTexture(GL_TEXTURE_2D, textureid_P1[14]);}
    glColor4f(1.0f,1.0f,1.0f, 0.5f);
    drawSquare(1.2f - ((((half_width * 0.175f) * 2) + pad) * 2.0f), yLoc, 0, half_width * 0.175f, half_height * 0.0625f);
    glBindTexture(GL_TEXTURE_2D, textureid_P1[15]);

    //Draw Single
    if (curMenuButton == 3)
    {glBindTexture(GL_TEXTURE_2D, textureid_P1[16]);}
    glColor4f(1.0f,1.0f,1.0f, 0.5f);
    drawSquare(1.2f - ((((half_width * 0.175f) * 2) + pad) * 3.0f), yLoc, 0, half_width * 0.175f, half_height * 0.0625f);
    glBindTexture(GL_TEXTURE_2D, textureid_P1[17]);

    //Draw Single
    if (curMenuButton == 4)
    {glBindTexture(GL_TEXTURE_2D, textureid_P1[18]);}
    glColor4f(1.0f,1.0f,1.0f, 0.5f);
    drawSquare(1.2f - ((((half_width * 0.175f) * 2) + pad) * 4.0f), yLoc, 0, half_width * 0.175f, half_height * 0.0625f);
    


    //ship
    glPushMatrix();
    //glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    if (shipAngle > 45)
    {shipRotation = -0.1f;}
    else if (shipAngle < 20)
    {shipRotation = 0.1f;}

    shipAngle += shipRotation;

    float newY = (shipAngle / 100.0f);  //newY = 0.5f
    glPushMatrix();
    glTranslatef(0,-newY,5.0f);
    glRotatef(75.0f,0.0f,1.0f,0.0f);
    glRotatef(shipAngle,0.0f,0.0f,1.0f);
    glScalef(0.0925f,0.0925f,0.0925f);
    glTranslatef(0,newY,0.0f);

    //glPopAttrib();
    //glPopMatrix();
    //draw particle
    //glPushMatrix();
   // glPushAttrib(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST);
    //glLoadIdentity();
    //glOrtho(-1, 1, -1, 1, -10.0f, 1000.0f);
    //setUpPerpView();
    Particle* newParticle = new Particle(shipAngle * 0.1f,0.0f,shipAngle * 0.03f + 1.0f);
    newParticle->setVelocity(NxVec3(0.0f,shipAngle * 0.001f,1.5));
    newParticle->timeTilDeath = 20;
    particles.push_back(newParticle);
    Particle* newParticle2 = new Particle(shipAngle * -0.1f,0.0f,shipAngle * 0.04f + 1.0f);
    newParticle2->setVelocity(NxVec3(0.0f,(shipAngle * -0.01f)+0.2f,1.7f));
    newParticle2->timeTilDeath = 20;
    particles.push_back(newParticle2);

    glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
    for (unsigned int x=0;x<particles.size();x++)
    {
        glPushMatrix();
        glScalef(0.7f,0.7f,0.7f);
        glTranslatef(particles[x]->getLocation().x,particles[x]->getLocation().y,particles[x]->getLocation().z);
        
        //glRotatef(75.0f,0.0f,1.0f,0.0f);
        //glRotatef(shipAngle,0.0f,0.0f,1.0f);
        //glScalef(0.0725f,0.0725f,0.0725f);
        //glTranslatef(-particles[x]->getLocation().x,-particles[x]->getLocation().y,-particles[x]->getLocation().z);
        modelManager;

            drawModel(modelManager.getModel(0),0,0,0,1.0f);
        glPopMatrix();
    }

    updateParticles();
    glPopMatrix();



    
    //draw mothership 7&8

    //if (shipAngle > 45)
    //{shipRotation = -0.1f;}
    //else if (shipAngle < 20)
    //{shipRotation = 0.1f;}

    

    

    /*
    glTranslatef(0,-newY,5.0f);
    glRotatef(75.0f,0.0f,1.0f,0.0f);
    glRotatef(shipAngle,0.0f,0.0f,1.0f);
    glScalef(0.0925f,0.0925f,0.0925f);
    glTranslatef(0,newY,-5.0f);
    */

    //draw ship
    glTranslatef(0,-newY,5.0f);
    glRotatef(75.0f,0.0f,1.0f,0.0f);
    glRotatef(shipAngle,0.0f,0.0f,1.0f);
    glScalef(0.0925f,0.0925f,0.0925f);
    glTranslatef(0,newY,-5.0f);

    glBindTexture(GL_TEXTURE_2D, textureid_P1[27]);
    drawModel(modelManager.getModel(7),0,0,0,1.0f);     //hull
    glBindTexture(GL_TEXTURE_2D, textureid_P1[28]);
    drawModel(modelManager.getModel(8),0,0,0,1.0f);     //engine


    glPopAttrib();
    glPopMatrix();
    //end particles


    //ship



    if (aShader != NULL)
    {
        aShader->off();
    }


    if (psi.isActive)
    {
        drawProfileOverlay(psi);
    }




    //Fader
    //float FadeCtrl = 0.0f;
    glColor4f(0.0f,0.0f,0.0f, updateFade(dt));
    	glBegin(GL_QUADS);
            glVertex3f(   (-half_width),    (+half_height),    (-0.02f)   );
		    glVertex3f(   (+half_width),    (+half_height),    (-0.02f)   );
		    glVertex3f(   (+half_width),    (-half_height),    (-0.02f)   );
		    glVertex3f(   (-half_width),    (-half_height),    (-0.02f)   );
		glEnd();

        if (FadeCtrl >= 1.0f)
            {
                FadeCtrl=0.0f;fadeMode=0;return 1;
            }


    if (aShader != NULL)
    {
        glDisable(GL_TEXTURE_2D);
    }


    drawText(800,-680, "MAIN MENU!");






    //glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHTING);
	glPopMatrix();

    return 0;
}


void RenderingEngine::drawProfileOverlay(ProfileScreenInfo psi)
{
    //clear depth buffer
    //glClear(GL_DEPTH_BUFFER_BIT);


    //Initialize a new coordinate system
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0f, 1.0f);
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //clear depth buffer
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    //declare some common variables
    const float half_height = SCREEN_HEIGHT / 2.0f;
    const float half_width = SCREEN_WIDTH / 2.0f;

    const float button_width = SCREEN_WIDTH / 6.0f;     //button width is /3, but also /2 as drawSquare uses half
    float const textWidth = button_width * 1.6f;

    const float dec_height = SCREEN_HEIGHT / 40.0f;
    const float butWidthOffset = half_width + (SCREEN_WIDTH / 96.0f);  //128 64
    const float butHeightOffset = (SCREEN_HEIGHT / 4.0f);

    const float titleHeightOffset = (SCREEN_HEIGHT / 8.0f);
    //const float doneHeightOffset = (3.0f * SCREEN_HEIGHT / 4.0f);// + (SCREEN_HEIGHT / 32.0f) ;
    const float doneHeightOffset = (13.0f * SCREEN_HEIGHT / 16.0f);// + (SCREEN_HEIGHT / 32.0f) ;

    //draw transparent blackground
        glColor4f(0.0f,0.0f,0.0f, 0.5f);
        drawSquare(half_width, half_height, 0.0f, half_width, half_height);
        glClear(GL_DEPTH_BUFFER_BIT);

    //draw profile info
        aHUDShader->on();

        glBindTexture(GL_TEXTURE_2D, textureid_P1[33]);
        glColor4f(0.0f,0.0f,0.0f, 1.0f);
        drawSquareUVRev(half_width, half_height, 0.0f, half_width, half_height);

        //Title
        string title = "Profile: Player 1";
        renderText(butWidthOffset-((textWidth)/2), titleHeightOffset, dec_height*2.0f, (textWidth)/title.size(), 36, title, true);
        //drawSquareUVRev(butWidthOffset, titleHeightOffset, 0.0f, button_width, dec_height);


        //Profiles
        title = "Default";
        if (psi.selectedItem == 1)
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*3), dec_height*1.8f, (textWidth)/title.size(), 35, title, true);
        else
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*3), dec_height*1.8f, (textWidth)/title.size(), 34, title, true);

        title = "Ankle Skylocker";
        if (psi.selectedItem == 2)
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*5), dec_height*1.8f, (textWidth)/title.size(), 35, title, true);
        else
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*5), dec_height*1.8f, (textWidth)/title.size(), 34, title, true);

        title = "Shinobi Kanobi";
        if (psi.selectedItem == 3)
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*7), dec_height*1.8f, (textWidth)/title.size(), 35, title, true);
        else
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*7), dec_height*1.8f, (textWidth)/title.size(), 34, title, true);

        title = "Doda";
        if (psi.selectedItem == 4)
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*9), dec_height*1.8f, (textWidth)/title.size(), 35, title, true);
        else
            renderText(butWidthOffset-((textWidth)/2), titleHeightOffset+(dec_height*9), dec_height*1.8f, (textWidth)/title.size(), 34, title, true);
        /*
        if (psi.selectedItem == 1)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*0), 0.0f, button_width, dec_height);
        

        if (psi.selectedItem == 2)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*2), 0.0f, button_width, dec_height);

        if (psi.selectedItem == 3)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*4), 0.0f, button_width, dec_height);

        if (psi.selectedItem == 4)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*6), 0.0f, button_width, dec_height);

       if (psi.selectedItem == 5)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*8), 0.0f, button_width, dec_height);

        if (psi.selectedItem == 6)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, butHeightOffset + (dec_height*10), 0.0f, button_width, dec_height);
        */

        //Done Button
       if (psi.selectedItem == 0)
            glBindTexture(GL_TEXTURE_2D, textureid_P1[1]);
        else
            glBindTexture(GL_TEXTURE_2D, textureid_P1[0]);
        drawSquareUVRev(butWidthOffset, doneHeightOffset, 0.0f, button_width, dec_height);

        aHUDShader->off();

    //reset to previous state
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

     glEnable(GL_LIGHTING);

}




void RenderingEngine::drawWheels(Entity* entity, int model, int texture)
{
    if (entity->getDriveWheels()->size() > 0)
    {
        for (unsigned d = 0; d < entity->getDriveWheels()->size(); ++d)
        {
            glBindTexture(GL_TEXTURE_2D, textureid_P1[texture]);
            NxMat34* aPose = &(entity->getDriveWheels()->at(d)->getGlobalPose());
            drawModelPos(modelManager.getModel(model), aPose );
        }
    }

    if (entity->getPassiveWheels()->size() > 0)
    {
        for (unsigned d = 0; d < entity->getPassiveWheels()->size(); ++d)
        {
            glBindTexture(GL_TEXTURE_2D, textureid_P1[texture]);
            NxMat34* aPose = &(entity->getPassiveWheels()->at(d)->getGlobalPose());
            drawModelPos(modelManager.getModel(model), aPose );
        }
    }
}

void RenderingEngine::drawShadow(Entities* entities, NxScene* scene)
{
	NxRay ray;
    NxRaycastHit hit;
	NxVec3 down(0.0f, -1.0f, 0.0f);

	ray.dir = down;

    if (entities->cars.size() > 0)
    {
        for (unsigned i = 0; i < entities->cars.size(); ++i)
        {
            if (entities->cars[i]->rc.size() > 0)
            {
                for (unsigned r = 0; r < entities->cars[i]->rc.size(); ++r)
                {
					ray.orig = entities->cars[i]->getActor()->getGlobalPosition();

					scene->raycastClosestShape(ray,NX_ALL_SHAPES,hit);
					NxVec3 result = hit.worldImpact - ray.orig;

                    //glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->cars[i]->rc[r]->textureID]);
                    NxMat34* aPose = &(entities->cars[i]->getActor()->getGlobalPose());
                    NxMat33 aRot = (entities->cars[i]->getActor()->getGlobalOrientation());
					NxVec3* aim = &(entities->cars[i]->getActor()->getGlobalPosition());
					glPushMatrix();

 					float mat[16];
					//aPose->getColumnMajor44(mat);
                    aRot.getColumnMajor(mat);
					//float distToGround = -0.35f;

					
                    NxVec3 theVec = NxVec3(aim->x,hit.worldImpact.y + 1.0f,aim->z);

                    //theVec = entities->cars[i]->getActor()->getGlobalOrientation() * theVec;
                    //glMultMatrixf(mat);
					glTranslatef(theVec.x, theVec.y, theVec.z);
                    //glMultMatrixf(mat);
                    //glTranslatef(-theVec.x, -theVec.y, -theVec.z);

					//glTranslatef(aim->x,hit.worldImpact.y + 1.0f,aim->z);

					for (unsigned x = 0; x < entities->cars[i]->rc.size();x++)
					//{drawModel(modelManager.getModel(entities->cars[i]->rc[x]->modelID), 0.0f, 0, 0, 1.0f );}
                    {drawModel(modelManager.getModel(0), 0.0f, 0, 0, 1.0f );}
                    glPopMatrix();

                }
            }
            else
            {
                //glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                drawActor(entities->cars[i]->getActor());
            }
        }
    }
}

void RenderingEngine::drawCars(Entities* entities)
{
    if (entities->cars.size() > 0)
    {
        for (unsigned i = 0; i < entities->cars.size(); ++i)
        {
            if (entities->cars[i]->rc.size() > 0)
            {
                for (unsigned r = 0; r < entities->cars[i]->rc.size(); ++r)
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->cars[i]->rc[r]->textureID]);
                    NxMat34* aPose = &(entities->cars[i]->getActor()->getGlobalPose());
                    //drawModel(modelManager.getModel(entities->cars[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
                    drawModelPos(modelManager.getModel(entities->cars[i]->rc[r]->modelID), aPose );
                    if(entities->cars[i]->getShield())
                        drawModelPos(modelManager.getModel("Shield.obj"), aPose );
                    //Particles
                    //Particle* newParticle = new Particle(entities->cars[i]->getActor()->getGlobalPose().t.x, entities->cars[i]->getActor()->getGlobalPose().t.y,entities->cars[i]->getActor()->getGlobalPose().t.z);
                    //particles.push_back(newParticle);

                }
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                drawActor(entities->cars[i]->getActor());
            }
        }
    }
}
void RenderingEngine::drawDynamicObjects(std::vector<Entity*>* dObjs)
{
    for(unsigned i=0;i<dObjs->size();i++)
    {
        if(dObjs->at(i)->isAlive())
        {
            for (unsigned r=0; r < dObjs->at(i)->rc.size();r++)
            {
                glBindTexture(GL_TEXTURE_2D, textureid_P1[dObjs->at(i)->rc[r]->textureID]);
                drawModelPos(modelManager.getModel(dObjs->at(i)->rc[r]->modelID),&(dObjs->at(i)->getActor()->getGlobalPose()));
            }
        }
            //drawModelPos(dObjs->at(i)->getModel(),&(dObjs->at(i)->getActor()->getGlobalPose()));
    }
}

void RenderingEngine::drawAICars(Entities* entities)
{
    if (entities->AIcars.size() > 0)
    {
        for (unsigned i = 0; i < entities->AIcars.size(); ++i)
        {
            if (entities->AIcars[i]->rc.size() > 0)
            {
                for (unsigned r = 0; r < entities->AIcars[i]->rc.size(); ++r)
                {
                    glBindTexture(GL_TEXTURE_2D, textureid_P1[entities->AIcars[i]->rc[r]->textureID]);
                    NxMat34* aPose = &(entities->AIcars[i]->getActor()->getGlobalPose());
                    //drawModel(modelManager.getModel(entities->AIcars[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
                    drawModelPos(modelManager.getModel(entities->AIcars[i]->rc[r]->modelID), aPose );

                    if(entities->AIcars[i]->getShield())
                        drawModelPos(modelManager.getModel("Shield.obj"), aPose );

                    //myTargetVector
                    glBindTexture(GL_TEXTURE_2D, 5);
                    glBegin(GL_TRIANGLE_STRIP);
                        glNormal3f(1.0f, 0.0f, 0.0f);
		                //glTexCoord2d(0.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myTargetVector.x-0.6f,entities->AIcars.at(i)->aAI->myTargetVector.y,entities->AIcars.at(i)->aAI->myTargetVector.z);
                        //glTexCoord2d(1.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myTargetVector.x,entities->AIcars.at(i)->aAI->myTargetVector.y+20.2f,entities->AIcars.at(i)->aAI->myTargetVector.z);
                        //glTexCoord2d(0.0,1.0); glVertex3f(entities->AIcars.at(i)->aAI->myTargetVector.x+0.2f,entities->AIcars.at(i)->aAI->myTargetVector.y,entities->AIcars.at(i)->aAI->myTargetVector.z);
                        glTexCoord2d(0.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myTargetVector.x + entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->aAI->myTargetVector.y + entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->aAI->myTargetVector.z + entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                        glTexCoord2d(1.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myTargetVector.x + entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->aAI->myTargetVector.y+2.2f + entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->aAI->myTargetVector.z + entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                        glTexCoord2d(0.0,1.0); glVertex3f(entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                    glEnd();

                    glBindTexture(GL_TEXTURE_2D, 6);
                    glBegin(GL_TRIANGLE_STRIP);
                        glNormal3f(1.0f, 0.0f, 0.0f);
		                glTexCoord2d(0.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myOrientation.x + entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->aAI->myOrientation.y + entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->aAI->myOrientation.z + entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                        glTexCoord2d(1.0,0.0); glVertex3f(entities->AIcars.at(i)->aAI->myOrientation.x + entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->aAI->myOrientation.y+2.0f+entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->aAI->myOrientation.z+entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                                                glTexCoord2d(0.0,1.0); glVertex3f(entities->AIcars.at(i)->getActor()->getGlobalPose().t.x,entities->AIcars.at(i)->getActor()->getGlobalPose().t.y,entities->AIcars.at(i)->getActor()->getGlobalPose().t.z);
                    glEnd();


                    //drawModel(0, entities->AIcars.at(i)->aAI->myTargetVector.x,entities->AIcars.at(i)->aAI->myTargetVector.y,entities->AIcars.at(i)->aAI->myTargetVector.z, 1.0f);
                }
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
                drawActor(entities->AIcars[i]->getActor());
            }
        }
    }
}

void RenderingEngine::drawObstacles(Entities* entities)
{
    if (entities->Obstacles.size() > 0)
    {
        for (unsigned i = 0; i < entities->Obstacles.size(); ++i)
        {
            if (entities->Obstacles[i]->rc.size() > 0)
            {
                for (unsigned r = 0; r < entities->Obstacles[i]->rc.size(); ++r)
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
                    printf("Obstacles has no actors\n");
                else
                {
                    //drawActor_Safe(entities->Obstacles[i]->getActor());
                    //drawActor(entities->Obstacles[i]->getActor());
                }
            }
        }
    }
}

void RenderingEngine::drawStaticObjs(Entities* entities)
{
    if (entities->StaticObjs.size() > 0)
    {
        for (unsigned i = 0; i < entities->StaticObjs.size(); ++i)
        {
            if (entities->StaticObjs[i]->rc.size() > 0)
            {
                for (unsigned r = 0; r < entities->StaticObjs[i]->rc.size(); ++r)
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
                    printf("StaticObj has no actors\n");
                else
                {
                    //drawActor_Safe(entities->StaticObjs[i]->getActor());
                    //drawActor(entities->StaticObjs[i]->getActor());///BUGGY
                }
            }
        }
    }
}

void RenderingEngine::drawTrack(Track* track)
{
    if (track->getEntity()->rc.size() > 0)
    {
        for (unsigned r = 0; r < track->getEntity()->rc.size(); ++r)
        {
            glBindTexture(GL_TEXTURE_2D, textureid_P1[track->getEntity()->rc[r]->textureID]);
            NxMat34* aPose = &(track->getEntity()->getActor()->getGlobalPose());

            if(track->getEntity()->getUsingDisplayList())
                drawDisplayList(track->getEntity()->getDisplayListIndex());
            else
                drawModelPos(modelManager.getModel(track->getEntity()->rc[r]->modelID), aPose );
            //drawModel(modelManager.getModel(entities->Track[i]->rc[i]->modelID), aPose->t.x, aPose->t.y, aPose->t.z, 1.0f );
        }
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, textureid_P1[6]);
        if (track->getEntity()->getActor() == NULL)
        {printf("Track has no actors\n");}
        else
        {
//                   drawActor(entities->Track[i]->getActor());///BUGGY
        }
    }
    //Draw the waypoints on the track

    
    std::vector<Waypoint*>* wps = track->getWaypoints();
    ObjModel* model = modelManager.getModel("box.obj");
    if (model != NULL)
    {                
        for(unsigned int i=0; i<wps->size(); i++)       
        {
            if(wps->at(i)->type == Waypoint::PICKUP_SPAWN)
            {
                model = modelManager.getModel("Shield.obj");

                if(model != NULL)
                    drawModel(model,wps->at(i)->pos.x,wps->at(i)->pos.y+2,wps->at(i)->pos.z,1);
            }
            /*else if(wps->at(i)->type == Waypoint::WAYPOINT)
                model = modelManager.getModel("box.obj");*/

        }
    }
    
        
}


void RenderingEngine::drawActor_Safe(NxActor* actor)
{
    glPushMatrix();
    NxMat34 aPose = actor->getGlobalPose();
 	float mat[16];
	aPose.getColumnMajor44(mat);
   // 
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

void RenderingEngine::drawSquare(float x, float y, float z, float half_width, float half_height)
{
		glBegin(GL_QUADS);
		//Bottom
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2d(1.0,1.0); glVertex3f(   (x-half_width),    (y+half_height),    (z)   );
		glTexCoord2d(0.0,1.0); glVertex3f(   (x+half_width),    (y+half_height),    (z)   );
		glTexCoord2d(0.0,0.0); glVertex3f(   (x+half_width),    (y-half_height),    (z)   );
		glTexCoord2d(1.0,0.0); glVertex3f(   (x-half_width),    (y-half_height),    (z)   );
		glEnd();
}

void RenderingEngine::drawSquareUVRev(float x, float y, float z, float half_width, float half_height)
{
		glBegin(GL_QUADS);
		//Bottom
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(   (x-half_width),    (y+half_height),    (z)   );
		glTexCoord2d(1.0,0.0); glVertex3f(   (x+half_width),    (y+half_height),    (z)   );
		glTexCoord2d(1.0,1.0); glVertex3f(   (x+half_width),    (y-half_height),    (z)   );
		glTexCoord2d(0.0,1.0); glVertex3f(   (x-half_width),    (y-half_height),    (z)   );
		glEnd();
}


void RenderingEngine::drawSkyBox(float x, float y, float z, float width, float height, float length, int textureID)
{
    //const int FRONT = 1;
    //const int FRONT = 1;

	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

    glNormal3f(0.0f, 0.0f, 0.0f);
    glColor3f(1.0f,1.0f,1.0f);
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[20]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[21]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[23]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[22]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[24]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, textureid_P1[25]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	glEnd();
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

void RenderingEngine::startFadeIn()
{
//    if (fadeMode == 0)
    {
        FadeCtrl = 1.0f;
        fadeMode = 1;
    }
}

void RenderingEngine::startFadeOut()
{
//    if (fadeMode == 0)
    {
        FadeCtrl = 0.0f;
        fadeMode = 2;
    }
}

float RenderingEngine::updateFade(float dt)
{
    switch (fadeMode)
    {
    case 0: //Stopped
        break;

    case 1: //Fade In
        if (FadeCtrl > 0)
        {FadeCtrl = FadeCtrl - 0.01f;}
        else
        {FadeCtrl = 0.0f;fadeMode = 0;}
        break;

    case 2: //Fade Out
        if (FadeCtrl < 1.0f)
        {FadeCtrl = FadeCtrl + 0.01f;}
        else
        {FadeCtrl = 1.0f;fadeMode = 0;}
        break;
    
    }
    return FadeCtrl;
    
}

void RenderingEngine::updateParticles()
{

    
//    for (vector<Particle>::iterator it=particles.begin(); 
//                              it!=particles.end(); 
//                              )
//    {
    for (unsigned int x=0;x<particles.size();x++)
    {

       if(particles[x]->isDead())
       {
          //it = particles.erase(it);
           particles.erase(particles.begin()+x);
       }
       else
       {
          particles[x]->Age();
          particles[x]->Move();
       }
     }
     


}
