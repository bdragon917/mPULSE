#pragma once
#include "GameState.h"
#include "RenderingEngine.h"

class InitState : public GameState
{
public:    
    static InitState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);

private:
    InitState();
    RenderingEngine* renderer;
};
