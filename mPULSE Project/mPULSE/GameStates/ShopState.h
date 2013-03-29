#pragma once

#define NOMINMAX
#include <vector>
#include <map>
#include <Util/Clock.h>

#include <GameStates/GameState.h>
#include <RenderingEngine/RenderingEngine.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <SoundEngine/SoundEngine.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <GameStates/GameVariables.h>
#include <RenderingEngine\ShopScreenInfo.h>

class ShopState : public GameState
{
public:
    static ShopState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);
    void reset();


private:
    ShopState();

    ShopScreenInfo ssi;
    DynamicImage* mechanicGirl;
    DynamicImage* painterGirl;

    bool lockControls;
    bool endState;

    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    SoundEngine* soundEngine;
    GameVariables* gameVariables;

    Clock clock;

    void keySelectLeft();
    void keySelectRight();
    void keySelectUp();
    void keySelectDown();
    void keySelectTarget();


    void backPressed();

    void enterMechanic();
    void enterPainter();

    float myDt; //hack for update

    int curSelectedX;
    int curSelectedY;
    int MAX_X_SELECTED;
    int MAX_Y_SELECTED;

    //xbox controller variables
    int WAIT_TIME;
    bool buttonPressed;
    unsigned prevTime;
};