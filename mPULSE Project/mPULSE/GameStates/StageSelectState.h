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
#include <GameStates\PlayState.h>

class StageSelectState : public GameState
{
public:
    static StageSelectState* getInstance();
	void initialize();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    StageSelectState();

    ShopScreenInfo ssi;

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

    void loadTrack();

    void backPressed();

    float myDt; //hack for update

    int currentSelectedX;
    int currentSelectedY;
    int MAX_X_SELECTED;
    int MAX_Y_SELECTED;

    //xbox controller variables
    int WAIT_TIME;
    bool buttonPressed;
    unsigned prevTime;
};