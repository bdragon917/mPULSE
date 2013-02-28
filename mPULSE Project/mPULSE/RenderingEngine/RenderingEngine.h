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
#include "../InGameObjects\Entities\Entity.h"
#include "..\ModelLoader\ModelManager.h"
#include "..\ModelLoader\ObjModel.h"
#include <math.h>
#include "../InGameObjects/Track.h"
#include "Particle.h"

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
void createLight_MainMenu();
void setUpPerpView();
void setUpOrthoView();
//Draw Functions
int drawIntro();
void moveStuff(float &testF);


void drawScene(NxScene* scene,Track* track, Entities* entities);
void drawScene_ForPlayer(NxScene* scene, Track* track, Entities* entities, int carIndex, bool splitScreen);
int drawMainMenuScreen(int curMenuButton, bool clicked);



void drawActor(NxActor* actor);
void drawActor_Safe(NxActor* actor);
void drawShape(NxShape* shape);
void drawBox(NxBoxShape* box);
void drawBox_Generic(float size);
void drawSquare(float x, float y, float z, float half_width, float half_height);
void drawModel(ObjModel* model,int x,int y, int z, int scale);
void drawModelPos(ObjModel* model, NxMat34* aMatrix);
void drawModelShadow(ObjModel* model, NxMat34* aPose);
GLuint generateDisplayList(std::string modelName,int x,int y,int z,int scale);
GLuint generateDisplayList(ObjModel* model,int x,int y,int z,int scale);
void deleteDisplayList(GLuint index);
void drawDisplayList(int index);

    Console aConsole;    
    Shader* aShader;
    Shader* aShadowShader;

    string FloatToString(float input);

    //used for scene display
    bool debugPhysX;
    bool showScene;
    bool debugCamera;

    //Texture Stuff
    GLuint* textureid_P1;

    //Fade stuff
    void startFadeIn();
    void startFadeOut();


    ModelManager getModelManger();

    void setPlayerNum(int num);

private:
    RenderingEngine();

    std::vector<Particle*> particles;
    void updateParticles();

    std::vector<GLuint> displayLists;
    ModelManager modelManager;

    void drawGroundPlane(float xoffset, float yoffset);
    void drawCheckerBoard(float x, float y);

    void drawSkyBox(float x, float y, float z, float width, float height, float length, int textureID);

    void drawWheels(Entity* entity, int model, int texture);
    void drawCars(Entities* entities);
    void drawAICars(Entities* entities);
    void drawObstacles(Entities* entities);
    void drawStaticObjs(Entities* entities);
    void drawTrack(Track* track);

    void RenderDebugPhysic(const NxDebugRenderable* ndr);
    
    //Console Variables
    bool showConsole;
    void displayConsole();

    void bindBMPtoTexture(char* filename, GLuint textures);
    void initializeTexture();

    int playerNum;

    //Used for Fade In and Out
    float FadeCtrl;
    int fadeMode;
    float updateFade(); 
    
        
        //    int loadShaders();
        //Used to generate a list of shaders
 //       typedef enum {
 //       CAR
 //   } ShaderType;
    
 //   CONST int ShaderTypeNum = 1;

    //ShadowMap Stuff
    //{
    void generateShadowFBO();
    void setTextureMatrix(void);
    void setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z);

    #define RENDER_WIDTH 640.0
    #define RENDER_HEIGHT 480.0
    #define SHADOW_MAP_RATIO 2


    //Camera position
    float p_camera[3];

    //Camera lookAt
    float l_camera[3];

    //Light position
    float p_light[3];

    //Light lookAt
    float l_light[3];


    //Light mouvement circle radius
    float light_mvnt;

    // Hold id of the framebuffer for light POV rendering
    GLuint fboId;

    // Z values will be rendered to this texture when using fboId framebuffer
    GLuint depthTextureId;

    // Use to activate/disable shadowShader
    GLhandleARB shadowShaderId;
    GLuint shadowMapUniform;
    //}


};