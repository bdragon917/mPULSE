#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    cars.push_back(new Entity);
    //cars.addAppearance(new Appearance("some appearance data"))
    //cars.addPhysics(new Appearance("some physics data"))
    //physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
	renderingEngine->initializeGL();
}

void PlayState::update(float dt)
{    
    //physicsEngine->Simulate(dt,&cars[0]->getPhysData());
}

void PlayState::render()
{
    //renderingEngine->Render(&cars[0]->getAppearance())	
	renderingEngine->draw();
}

bool PlayState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    return true;
}

PlayState* PlayState::getInstance()
{    
    printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}