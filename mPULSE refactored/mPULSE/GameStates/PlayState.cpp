#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    cars.push_back(new Entity);

    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(&cars);
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
                {renderingEngine->aConsole.propragateMsg("Number of elements in cars: " + renderingEngine->FloatToString(cars.size()));}

                if (renderingEngine->aConsole.consoleString == "num actors")
                {renderingEngine->aConsole.propragateMsg("Number of actors in scene: " + renderingEngine->FloatToString(physicsEngine->getScene()->getNbActors()));}

                if (renderingEngine->aConsole.consoleString == "num debugphysic")
                {
                    renderingEngine->aConsole.propragateMsg("Number of Lines in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbLines()));
                    renderingEngine->aConsole.propragateMsg("Number of Points in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbPoints()));
                    renderingEngine->aConsole.propragateMsg("Number of Triangles in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbTriangles()));
                }
                
                //Get Commands
                //if (renderingEngine->aConsole.consoleString == "get testwheel")
                //{renderingEngine->aConsole.consoleString = "Test Wheel Torgue: " + renderingEngine->FloatToString(cars.at(0)->aWheel1->getMotorTorque());renderingEngine->aConsole.propragateMsg();}

                //tog Commands
                if ((renderingEngine->aConsole.consoleString == "tog debugphysic") || (renderingEngine->aConsole.consoleString == "tog dp"))
                {
                    if (renderingEngine->debugPhysX){renderingEngine->debugPhysX=false;renderingEngine->showScene=true;}else{renderingEngine->debugPhysX=true;renderingEngine->showScene=false;}; 
                }
                if (renderingEngine->aConsole.consoleString == "tog showscene")
                {
                    if (renderingEngine->showScene){renderingEngine->showScene=false;}else{renderingEngine->showScene=true;}; 
                }

                //set Commands

                
                //master Commands
                if (renderingEngine->aConsole.consoleString == "quit")
                {
                    renderingEngine->aConsole.propragateMsg("Trying to Quit...");
                    return false;
                }


                renderingEngine->aConsole.propragateMsg();

            }
            else if(keyPressed == SDLK_UP)
                renderingEngine->aConsole.goUp();
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
	
    //physicsEngine->ApplyForceToBox(NxVec3(state->leftStick.x,0.0,-(state->leftStick.y)), state->rTrigger*25000);

    float trig = state->rTrigger*25000.0f;
    NxVec3 v3 = NxVec3(0, 250000.0f,0);
    NxVec3 v0 = NxVec3(0, 0,0);


    //PROBLEM IS THAT ENTITY DOESN"T ACTUALLY HAVE A POINTER TO THE CAR!!!!!! - fixed
    //
    //theCar is another variable used to transmit the point, but this doesn't work (can delete this)
    //
    //The cars and theCar should have pointers added in setupPlayScene in physicsEngine.cpp
    if (state->a)
    {
        if (!(cars[0]->aWheel1 == NULL))
            cars[0]->aWheel1->getActor().setAngularVelocity(v3);
        else
            printf("NULL WHEEL0 at Cars[0]\n");
    }

    if (state->b)
    {
        if (!(cars.at(0)->aWheel1 ==NULL))
        {cars.at(0)->aWheel1->getActor().addForce(v3);}
        else
        {printf("NULL WHEEL0 at Cars[0]\n");}
    }
    if (state->x)
    {
        if (!(cars.at(0)->components.at(0) == NULL))
        {cars.at(0)->components.at(0)->getActor()->addForce(v3);}
        else
        {printf("NULL Cars[0]\n");}
    }
    if (state->y)
    {
        if (!(cars.at(0)->components.at(0) == NULL))
        {cars.at(0)->components.at(0)->getActor()->moveGlobalPosition(v0);}
        else
        {printf("NULL Cars[0]\n");}
    }

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