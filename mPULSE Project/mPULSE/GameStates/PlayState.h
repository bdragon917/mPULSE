#pragma once

#define NOMINMAX

#include <vector>
#include <map>

#include <GameStates/GameState.h>
#include <GameStates/GameVariables.h>

#include <RenderingEngine/RenderingEngine.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <SoundEngine/SoundEngine.h>

#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <InGameObjects/Track.h>
#include <InGameObjects/Pickups/Pickup.h>
#include <InGameObjects/Pickups/Barrier.h>
#include <InGameObjects/Pickups/MissileLauncher.h>
#include <InGameObjects/Pickups/Shield.h>

class PlayState : public GameState
{
public:
    static PlayState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);
    void PlayState::handleXboxController(int player, std::vector<Entity*> thing ,XboxController* state);
    void InitializeConsoleCommands();

private:
    bool showConsole;
    bool rbPressed;
    PlayState();

    Track* track;
    RenderingEngine::Entities entities;
    PhysicsEngine* physicsEngine;
	SoundEngine* soundEngine;
    RenderingEngine* renderingEngine;
    GameVariables* gameVariables;

    void PlayState::logReplay(int player, XboxController* state, float dt);
    void PlayState::logWayPoint(int player);

    std::map<std::string, int(*)(int)> commands;

    //Console Command Stuff!!!!// ADD commands here!
};

