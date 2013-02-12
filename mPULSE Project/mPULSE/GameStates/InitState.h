#pragma once

#define NOMINMAX
#include "GameState.h"
#include "../Util/Clock.h"
#include "../RenderingEngine/RenderingEngine.h"

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
    Clock clock;
    unsigned int time;
    static const int TIMEOUT = 3000;
};