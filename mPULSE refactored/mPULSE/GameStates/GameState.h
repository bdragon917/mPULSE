#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <SDL.h>

class GameState
{
public:
    typedef enum {
        INIT,
        MAIN_MENU,
        PLAY,
        PAUSE,
        FINISHED
    } StateType;

    GameState();
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents) = 0;

    virtual StateType pollStateChange()
    {
        return stateType;
    }

    virtual void changeStateType(StateType type)
    {
        stateType = type;
    }

    StateType stateType;
private:
    
};

