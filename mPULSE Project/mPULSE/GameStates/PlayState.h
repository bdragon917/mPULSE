#pragma once

#define NOMINMAX

#include <vector>
#include <map>

#include <GameStates/GameState.h>
#include <GameStates/GameVariables.h>
#include <Util/Clock.h>
#include <InGameObjects/CustomData.h>

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

#include "EventManager/SoundEvent.h"
#include "EventManager/CollisionEvent.h"
#include "EventManager/WaypointEvent.h"
#include "EventManager/TriggerEvent.h"
#include "EventManager/EventManager.h"

#include <InGameObjects\Entities\Entities.h>

class PlayState : public GameState
{
public:
    static PlayState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);
    void PlayState::handleXboxController(int player, std::vector<Entity*> cars ,XboxController* state, bool isHuman);
    void InitializeConsoleCommands();
    void setNumberOfPlayers(int numOfPlayers);

    void handleEvents();
    void handleCollisionEvents();
    void handleSoundEvents();
    void handleTriggerEvents();
    void handleWaypointEvents();
    void calculateRankings();
    std::vector<Entity*>* getPlayersOnLap(int lap);
    std::vector<Entity*>* sortPlayersByWaypoint(std::vector<Entity*>* players);

private:

    //Custom Keyboard Variables for keyboard Controls
    bool keyAPressed;
    bool keyDPressed;
    bool keyWPressed;
    bool keySPressed;


    bool showConsole;
    bool rbPressed;
    PlayState();
    float id;
    Track* track;
    Entities entities;
    std::vector<Entity*>* rankings;

    PhysicsEngine* physicsEngine;
	SoundEngine* soundEngine;
    RenderingEngine* renderingEngine;
    GameVariables* gameVariables;
    EventManager* eventManager;

    void PlayState::logReplay(int player, XboxController* state, float dt);
    void PlayState::logWayPoint(int player);

    std::map<std::string, int(*)(int)> commands;
    Clock time;
    int numPlayers;
};

