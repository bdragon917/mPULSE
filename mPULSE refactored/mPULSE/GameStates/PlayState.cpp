#include "PlayState.h"


PlayState::PlayState()
{
    printf("play state");
    changeState(PLAY);
    cars.push_back(new Entity);
    //cars.addAppearance(new Appearance("some appearance data"))
    //cars.addPhysics(new Appearance("some physics data"))
    //physicsEngine = PhysicsEngine::getInstance();
    //renderingEngine = RenderingEngine::getInstance();
}

void PlayState::update(float dt)
{    
    //physicsEngine->Simulate(dt,&cars[0]->getPhysData());
}

void PlayState::render()
{
    //renderingEngine->Render(&cars[0]->getAppearance())
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