#pragma once

#define NOMINMAX
#include <SDL.h>
#include <windows.h>
#include <Xinput.h>
#include "GameState.h"
#include "InitState.h"
#include "PlayState.h"

class Game
{
public:
    Game();
    bool handleEvents();
    void update(float dt);
    void render();

    bool handleKeyboardMouseEvents(SDL_Event& KeyboardMouseState);
    void handleXboxEvents(int player,XINPUT_STATE* state);
    void checkStateChange();

	float curFPS;		//Used by mPULSE to rely fps info to renderer

private:
    GameState* state;
    GameState::StateType stateType;
};