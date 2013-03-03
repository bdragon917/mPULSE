#pragma once

#define NOMINMAX
#include <vector>
#include <map>
#include <Util/Clock.h>

#include <GameStates/GameState.h>
#include <RenderingEngine/RenderingEngine.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <GameStates/GameVariables.h>

class MainMenuState : public GameState
{
public:
    static MainMenuState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    MainMenuState();
    bool buttonPressed;
    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    GameVariables* gameVariables;
    Clock clock;
    int curSelected;
    unsigned prevTime;
    int WAIT_TIME;
};

