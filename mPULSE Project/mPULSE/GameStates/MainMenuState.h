#pragma once

#define NOMINMAX
#include <vector>
#include <map>
#include <Util/Clock.h>

#include <GameStates/GameState.h>
#include <RenderingEngine/RenderingEngine.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <SoundEngine\SoundEngine.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <GameStates/GameVariables.h>

class MainMenuState : public GameState
{
public:
    static MainMenuState* getInstance();
	void initialize();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    SoundEngine* soundEngine;
    MainMenuState();
    bool buttonPressed;
    bool endState;
    bool lockControls;
   
    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    GameVariables* gameVariables;
    Clock clock;
    unsigned prevTime;

    void keySelectLeft();
    void keySelectRight();
    void keySelectTarget();

    float myDt;

    int curSelected;
    int WAIT_TIME;
    int MAX_SELECTED;
};

