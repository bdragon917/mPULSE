#pragma once

#define NOMINMAX
#include <vector>
#include "GameState.h"
#include "../RenderingEngine/RenderingEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "../Entities/Entity.h"
#include "../Entities/RenderableComponent.h"
#include <map>
#include "GameVariables.h"

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

    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    GameVariables* gameVariables;

    int curSelected;
};

