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
#include <RenderingEngine\DynamicImage.h>

class StoryState : public GameState
{
public:
    static StoryState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    StoryState();

    bool lockControls;
    bool endState;

    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    SoundEngine* soundEngine;
    GameVariables* gameVariables;

    Clock clock;

    void keySelectLeft();
    void keySelectRight();
    void keySelectTarget();
    void backPressed();

    float myDt; //hack for update

    int curSelected;
    int MAX_SELECTED;

    //xbox controller variables
    int WAIT_TIME;
    bool buttonPressed;
    unsigned prevTime;
};