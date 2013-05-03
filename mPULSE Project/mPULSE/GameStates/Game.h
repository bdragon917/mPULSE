#pragma once

#define NOMINMAX
#include <SDL.h>
#include <windows.h>
#include <Xinput.h>
#include <GameStates/GameState.h>
#include <GameStates/InitState.h>
#include <GameStates/PlayState.h>
#include <GameStates/MainMenuState.h>
#include <GameStates/StoryState.h>
#include <GameStates/SettingState.h>
#include <GameStates/LoungeState.h>
#include <GameStates/ProfileState.h>
#include <GameStates/ShopState.h>
#include <GameStates/ResultState.h>
#include <GameStates/StageSelectState.h>
#include <GameStates/ControlScreenState.h>
#include <GameStates\CreditState.h>
#include <Util/Clock.h>

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
    bool quit;

private:
    Clock* gameClock;
    GameState* state;
    GameState::StateType stateType;
};