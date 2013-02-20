#pragma once

#define NOMINMAX
#include <vector>
#include "GameState.h"
#include "../RenderingEngine/RenderingEngine.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "../Entities/Entity.h"
#include "../Entities/RenderableComponent.h"
#include "../SoundEngine.h"
#include <map>

class PlayState : public GameState
{
public:
    static PlayState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);
    void InitializeConsoleCommands();

private:
    bool showConsole;
    
    PlayState();

    RenderingEngine::Entities entities;
    PhysicsEngine* physicsEngine;
	SoundEngine* soundEngine;
    RenderingEngine* renderingEngine;

    void PlayState::logReplay(int player, XboxController* state, float dt);

    std::map<std::string, int(*)(int)> commands;

    //Console Command Stuff!!!!// ADD commands here!
};

