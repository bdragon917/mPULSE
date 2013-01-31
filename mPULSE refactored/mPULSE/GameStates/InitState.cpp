#include "InitState.h"

InitState::InitState()
{
    stateType = INIT;
    renderer = RenderingEngine::getInstance();
    renderer->initializeGL();
    renderer->drawIntro2();    
    time = clock.getCurrentTime();
    printf("init state");
}

void InitState::update(float dt)
{    
    if((clock.getCurrentTime() - time) > TIMEOUT) //Just testing a timed state transition
        changeState(PLAY);

}
void InitState::render()
{
    
}
bool InitState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    return true;
}

InitState* InitState::getInstance()
{
    static InitState initState;    
    return &initState;
}