#pragma once

#define NOMINMAX
#include <GameStates/GameState.h>
#include <Util/Clock.h>
#include <RenderingEngine/RenderingEngine.h>
#include <SoundEngine/SoundEngine.h>
#include <GameStates/GameVariables.h>

class InitState : public GameState
{
public:    
    static InitState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    InitState();
    RenderingEngine* renderingEngine;
	SoundEngine* soundEngine;
    GameVariables* gameVariables;
    Clock clock;
    unsigned int time;
    static const int TIMEOUT = 3000;
};
