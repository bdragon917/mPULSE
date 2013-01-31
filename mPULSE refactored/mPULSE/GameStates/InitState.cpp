#include "InitState.h"

InitState::InitState()
{
    stateType = INIT;
    renderer = RenderingEngine::getInstance();
    renderer->initializeGL();
    renderer->drawIntro2();
}

void InitState::update(float dt)
{

}
void InitState::render()
{
    renderer->draw();
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