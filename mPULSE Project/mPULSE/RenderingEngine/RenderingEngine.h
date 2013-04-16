#pragma once

#define NOMINMAX
#define NO_SDL_GLEXT

#include <vector>
#include <math.h>
#include <sstream>	//String stream //for float convertion

#include <gl/glew.h>	//DONT MESS THIS ORDER!!!!
#include <gl/GLU.h>
#include <gl/GL.h>
#include <GL/glut.h>	//For text

#include <SDL.h>
#include <SDL_opengl.h>

#include <RenderingEngine/Shader.h>
#include <RenderingEngine/BMP.h>
#include <RenderingEngine/Particle.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <GameStates/Console.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Track.h>
#include <ModelLoader/ModelManager.h>
#include <ModelLoader/ObjModel.h>

#include <InGameObjects\Entities\Entities.h>

#include <RenderingEngine\ProfileScreenInfo.h>
#include <RenderingEngine\DynamicImage.h>

#include <GameStates\GameVariables.h>
#include <RenderingEngine\ShopScreenInfo.h>

class RenderingEngine
{
public:
    /*
    typedef struct
    {
        std::vector<Entity*> cars;
        std::vector<Entity*> AIcars;
        std::vector<Entity*> Obstacles;
        std::vector<Entity*> StaticObjs;
        std::vector<Entity*> DynamicObjs;
        std::vector<Entity*> Track;
    } Entities;
    */
    Entities* entities;

    static RenderingEngine* getInstance();
    float zRot;

    void ChangeResolution(int newWidthResolution, int newHeightResolution);
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    ///Custom Draw Functions
    void drawText(string s,float inX, float inY, float size=0.03);

    //void drawCube(float x, float y, float z, float size);
    void initializeGL();
    void quickInitialize();
    int drawControlScreen();
    void createLight();
    void createLight_MainMenu();
    void setUpPerpView();
    void setUpOrthoView();
    void setPerspective( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar, float xStretch, float yStretch );
    void setEntities(Entities* ents);
    //Draw Functions
    int drawIntro();
    void moveStuff(float &testF);

    void RenderingEngine::drawLoading();

    void drawScene(NxScene* scene,Track* track, Entities* entities);
    void drawScene_ForPlayer(NxScene* scene, Track* track, Entities* entities, int carIndex, bool splitScreen, bool topScreen, std::vector<Entity*> targetEntities);
    int drawMainMenuScreen(int curMenuButton, bool clicked, float dt, ProfileScreenInfo psi);
    int drawStoryScreen(float dt);
	int drawLoungeScreen(float dt);
    int drawSettingScreen(float dt, int selectX, int selectY);
    int drawShopScreen(float dt, ShopScreenInfo ssi);
    int drawResultScreen(float dt);
    int drawStageSelectScreen(float dt, int curSelected);
    int drawLoungeScreen(float dt, int curSelected);

    void drawProfileOverlay(ProfileScreenInfo psi);

    void RenderingEngine::renderText(float startX, float startY, float fontHeight, float fontWidth, int fontTexture, string str, bool invert);

    void drawActor(NxActor* actor);
    void drawActor_Safe(NxActor* actor);
    void drawShape(NxShape* shape);
    void drawBox(NxBoxShape* box);
    void drawBox_Generic(float size);
    void drawSquare(float x, float y, float z, float half_width, float half_height);
    void drawSquareUVRev(float x, float y, float z, float half_width, float half_height);
    void drawModel(ObjModel* model,int x,int y, int z, int scale);
    void drawModelPosRotationEnhanced(ObjModel* model, Entity* anEntity);
    void drawScaledModelPos(ObjModel* model, NxMat34* aPose, NxVec3 scale);
    void drawModel(ObjModel* model,int x,int y, int z, NxVec3 scale);
    void drawModelPos(ObjModel* model, NxMat34* aMatrix);
    void drawModelShadow(ObjModel* model, NxMat34* aPose);
    void drawDynamicObjects(std::vector<Entity*>* dObjs);
    GLuint generateDisplayList(std::string modelName,int x,int y,int z,int scale);
    GLuint generateDisplayList(ObjModel* model,int x,int y,int z,int scale);
    void deleteDisplayList(GLuint index);
    void drawDisplayList(int index);
	void drawShadow(Entities* entities, NxScene* scene);
    void RenderingEngine::drawShadow2(Entities* entities, NxScene* scene);

    Console aConsole;    
    Shader* aShader;
    Shader* aShinyShader;
    Shader* aSkyBoxShader;
    Shader* aShadowShader;
    Shader* aHUDShader;
	Shader* flatten;

    Shader* testRTShader;

    string FloatToString(float input);

    //used for scene display
    bool debugPhysX;
    bool showScene;
    bool debugCamera;

    //Texture Stuff
    GLuint* textureid_P1;

    //Transition stuff
	void startTransition(int type);

    void resetFade();
    void startFadeIn(unsigned fadeTimeLimit=1000);
    void startFadeOut(unsigned fadeTimeLimit=1000);

	typedef enum {
        FADE_IN,
        FADE_OUT,
        INSTANT,
        SLIDE,
		SLIDE_FADE
    } Resolution;


    ModelManager getModelManger();

    void setGameVariables(GameVariables* inGameVaribles);

    bool debugCam;

    float debugFloat;

private:
    
    struct drawableText {
        float x;
        float y;
        float size;
        std::string text;
    };

	struct asteroids {
		float scale;

		int texture;

		float angle;

		float rotateRate;

		float xVec;
		float yVec;
		float zVec;

		float x;
		float y;
		float z;
	};

    unsigned fadeTime;
    unsigned fadeStartTime;
    Clock clock;
    std::vector<drawableText> textQueue;

    std::vector<DynamicImage> dImages;

    RenderingEngine();

    std::vector<Particle*> particles;
    void updateParticles();

    std::vector<GLuint> displayLists;
    ModelManager modelManager;

	std::vector<asteroids> asteroidList;
	void generateAsteroids(int total);
	void turnAsteroids(int index);
	#define TOTAL_ASTEROIDS 200

    void drawGroundPlane(float xoffset, float yoffset);
    void drawCheckerBoard(float x, float y);

    void drawSkyBox(float x, float y, float z, float width, float height, float length, int textureID);

    void drawWheels(Entity* entity, int model, int texture);
    void drawCars(Entities* entities);
    void drawAICars(Entities* entities);
    void drawObstacles(Entities* entities);
    void drawStaticObjs(Entities* entities);
    void drawTrack(Track* track);

    void drawHUD(Entity* carEntity, bool hasWon);

    void RenderDebugPhysic(const NxDebugRenderable* ndr);
    
    //Console Variables
    bool showConsole;
    void displayConsole();

    void bindBMPtoTexture(char* filename, GLuint textures);
    void initializeTexture();

    //game Variables;
    GameVariables* gameVariables;


    void RenderingEngine::initializeMainMenuVariables();
    //MainMenu stuff
    float shipAngle;
    float shipRotation;

    //used to control the main texture alpha
    GLint locShader_Alpha;
    GLint locShader_DiscardBlue;

	//Transition Stuff
    //Used for Fade In and Out
    float FadeCtrl;
    int fadeMode;
    float updateFade(float dt);

    bool instantTrans;
        
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

    #define M_PI 3.14159265358979323846


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
