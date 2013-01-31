#pragma once
#include "GameState.h"
class PlayState : public GameState
{
public:
    static PlayState* getInstance();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);

private:
    PlayState();
};

