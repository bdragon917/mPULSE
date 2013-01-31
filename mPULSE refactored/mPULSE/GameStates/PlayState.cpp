#include "PlayState.h"


PlayState::PlayState()
{
    stateType = PLAY;
}

void PlayState::update(float dt)
{

}

void PlayState::render()
{
       
}

bool PlayState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    return true;
}

PlayState* PlayState::getInstance()
{    
    static PlayState playState;    
    return &playState;
}