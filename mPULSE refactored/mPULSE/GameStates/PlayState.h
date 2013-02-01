#pragma once
#include <vector>
#include "GameState.h"
#include "../RenderingEngine/RenderingEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "../Entities/Entity.h"

class PlayState : public GameState
{
public:
    static PlayState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);

private:
    PlayState();
    std::vector<Entity*> cars;
    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    float curFPS;
};

