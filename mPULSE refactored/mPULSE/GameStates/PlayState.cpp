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

            if (keyPressed == SDLK_BACKSPACE)
            {
                renderingEngine->aConsole.consoleString = renderingEngine->aConsole.consoleString.substr(0, renderingEngine->aConsole.consoleString.size() - 1);
            }
            else if (keyPressed == SDLK_RETURN)
            {
                //process command

                //Num Commands
                if (renderingEngine->aConsole.consoleString == "num cars")
                {renderingEngine->aConsole.consoleString = "Number of elements in cars: " + renderingEngine->FloatToString(cars.size());}

                if (renderingEngine->aConsole.consoleString == "num actors")
                {renderingEngine->aConsole.consoleString = "Number of actors in scene: " + renderingEngine->FloatToString(physicsEngine->getScene()->getNbActors());}

                if (renderingEngine->aConsole.consoleString == "num debugphysic")
                {
                    renderingEngine->aConsole.consoleString = "Number of Lines in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbLines());
                    renderingEngine->aConsole.propragateMsg();
                    renderingEngine->aConsole.consoleString = "Number of Points in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbPoints());
                    renderingEngine->aConsole.propragateMsg();
                    renderingEngine->aConsole.consoleString = "Number of Triangles in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbTriangles());
                }
                
                //Get Commands
                //if (renderingEngine->aConsole.consoleString == "get testwheel")
                //{renderingEngine->aConsole.consoleString = "Test Wheel Torgue: " + renderingEngine->FloatToString(cars.at(0)->aWheel1->getMotorTorque());renderingEngine->aConsole.propragateMsg();}

                //tog Commands
                if (renderingEngine->aConsole.consoleString == "tog debugphysic")
                {
                    if (renderingEngine->debugPhysX){renderingEngine->debugPhysX=false;}else{renderingEngine->debugPhysX=true;}; 
                }
                if (renderingEngine->aConsole.consoleString == "tog showscene")
                {
                    if (renderingEngine->showScene){renderingEngine->showScene=false;}else{renderingEngine->showScene=true;}; 
                }

                //set Commands

                
                //master Commands
                if (renderingEngine->aConsole.consoleString == "quit")
                {
                    renderingEngine->aConsole.consoleString = "Trying to Quit...";
                    return false;
                }


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
	
    physicsEngine->ApplyForceToBox(NxVec3(state->leftStick.x,0.0,-(state->leftStick.y)), state->rTrigger*25000);

    //cars.at(0)->aWheel1->setMotorTorque(trig);
    //cars.at(0)->aWheel1->setAxleSpeed(trig);
    //cars.at(0)->aWheel->motorTorque.setMotorTorque(trig);
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