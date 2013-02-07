#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    cars.push_back(new Entity);
    //cars.addAppearance(new Appearance("some appearance data"))
    //cars.addPhysics(new PhysicsData("some physics data"))
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
	renderingEngine->initializeGL();
    curFPS = 0.0f;
}

void PlayState::update(float dt)
{    
    curFPS = (1000/dt);
    physicsEngine->step();
}

void PlayState::render()
{
    //renderingEngine->Render(&cars[0]->getAppearance())	
	//renderingEngine->drawTest(curFPS);
	NxScene* scene = physicsEngine->getScene();
	renderingEngine->drawScene(scene);
}

bool PlayState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    return true;
}

void PlayState::handleXboxEvents(int player,XboxController* state)
{
	if(state->leftStick.magnitude > 0) {
		physicsEngine->ApplyForceToBox(NxVec3(state->leftStick.x,0.0,-(state->leftStick.y)), state->leftStick.magnitude*5);
	} else if(state->lb == true) {
		physicsEngine->resetBox();
	}
}

PlayState* PlayState::getInstance()
{    
    printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}