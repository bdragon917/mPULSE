#pragma once

#define NOMINMAX
#define NO_SDL_GLEXT



#include "gl/glew.h"	//DONT MESS THIS ORDER!!!!
#include "gl/GLU.h"
#include "gl/GL.h"

#include "Shader.h"

#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "GL\glut.h"			//For text

#include <sstream>	//String stream //for float convertion

//#include <NxPhysics.h>
#include "../PhysicsEngine/PhysicsEngine.h"

#include "BMP.h"
#include "..\GameStates\Console.h"
#include <vector>
#include "..\Entities\Entity.h"
#include "..\ModelLoader\ModelManager.h"
#include "..\ModelLoader\ObjModel.h"

class RenderingEngine
{
public:

typedef struct
{
    std::vector<Entity*> cars;
    std::vector<Entity*> AIcars;
    std::vector<Entity*> Obstacles;
    std::vector<Entity*> StaticObjs;
    std::vector<Entity*> Track;
} Entities;

static RenderingEngine* getInstance();
float zRot;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
///Custom Draw Functions
void prints(float inX, float inY, string s);
//void drawCube(float x, float y, float z, float size);
void initializeGL();
void createLight();
void setUpPerpView();
void setUpOrthoView();
//Draw Functions
int drawIntro();
void moveStuff(float &testF);
void drawScene(NxScene* scene, Entities* entities);
void drawActor(NxActor* actor);
void drawShape(NxShape* shape);
void drawBox(NxBoxShape* box);
void drawModel(ObjModel* model,int x,int y, int z, int scale);

    Console aConsole;    
    Shader* aShader;

    string FloatToString(float input);

    //used for scene display
    bool debugPhysX;
    bool showScene;

    //Texture Stuff
    GLuint* textureid_P1;

    ModelManager getModelManger();

private:
    RenderingEngine();
    ModelManager modelManager;

    void drawGroundPlane(float xoffset, float yoffset);
    void drawCheckerBoard(float x, float y);

    void RenderDebugPhysic(const NxDebugRenderable* ndr);
    
    //Console Variables
    bool showConsole;
    void displayConsole();





    void bindBMPtoTexture(char* filename, GLuint textures);
    void initializeTexture();

//    int loadShaders();
        //Used to generate a list of shaders
 //       typedef enum {
 //       CAR
 //   } ShaderType;
    
 //   CONST int ShaderTypeNum = 1;



};