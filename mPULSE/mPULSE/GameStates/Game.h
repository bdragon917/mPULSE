#pragma once

#define NOMINMAX
#include <SDL.h>
#include <windows.h>
#include <Xinput.h>
#include "GameState.h"
#include "InitState.h"
#include "PlayState.h"
#include "..\Util\Clock.h"

class Game
{
public:
    Game();
    bool handleEvents();
    void update();
    void render();

    bool handleKeyboardMouseEvents(SDL_Event& KeyboardMouseState);
    void handleXboxEvents(int player,XboxController* controller);
    void checkStateChange();

private:
    Clock* gameClock;
    GameState* state;
    GameState::StateType stateType;
};