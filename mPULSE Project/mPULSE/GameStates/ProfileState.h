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

class ProfileState : public GameState
{
public:
    static ProfileState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    ProfileState();

    ProfileScreenInfo psi;

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
    void ProfileState::backPressed();

    float myDt; //hack for update

    int targetPlayer;

    int curSelected;
    int MAX_SELECTED;

    //xbox controller variables
    int WAIT_TIME;
    bool buttonPressed;
    unsigned prevTime;
};