#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    cars.push_back(new Entity);
    //cars.addAppearance(new Appearance("some appearance data"))
    //cars.addPhysics(new PhysicsData("some physics data"))
    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(cars);
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


    //Console implimentation
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if (keyPressed == SDLK_RETURN)
            {
                if (renderingEngine->aConsole.consoleString == "num cars")
                {renderingEngine->aConsole.consoleString = "Number of elements in cars: " + renderingEngine->FloatToString(cars.size());}

                if (renderingEngine->aConsole.consoleString == "num actors")
                {renderingEngine->aConsole.consoleString = "Number of actors in scene: " + renderingEngine->FloatToString(physicsEngine->getScene()->getNbActors());}
                //process command
                //renderingEngine->aConsole
                
                renderingEngine->aConsole.propragateMsg();


            }
            else if ((keyPressed >= SDLK_SPACE) && (keyPressed <= SDLK_z ))
            {
                char c = keyPressed;
                renderingEngine->aConsole.consoleString = renderingEngine->aConsole.consoleString + c;
            }
         }
    
    return true;
}

void PlayState::handleXboxEvents(int player,XboxController* state)
{
	
    physicsEngine->ApplyForceToBox(NxVec3(state->leftStick.x,0.0,-(state->leftStick.y)), state->rTrigger*250);
	if(state->lb) {
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