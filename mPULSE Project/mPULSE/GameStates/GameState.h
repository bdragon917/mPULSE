#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <SDL.h>
#include <Input/XboxController.h>

class GameState
{
public:
    typedef enum {
        INIT,
        MAIN_MENU,
        STORY,
        SHOP,
        STAGE,
        SETTING,
        PROFILE,
        PLAY,
        RESULT,
        PAUSE,
        GAMEOVER
    } StateType;

    GameState();
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents) = 0;
    virtual void handleXboxEvents(int player,XboxController* state) = 0;

    StateType pollStateChange()
    {
        return stateType;
    }

    void changeState(StateType type)
    {
        stateType = type;
    }
    StateType stateType;


    bool quit;
};

