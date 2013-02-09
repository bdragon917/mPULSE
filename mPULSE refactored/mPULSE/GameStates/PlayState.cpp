#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    entities.cars.push_back(new Entity);
    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
	renderingEngine->initializeGL();
}

void PlayState::update(float dt)
{    
    physicsEngine->step(dt/1000);
}

void PlayState::render()
{    	    
	NxScene* scene = physicsEngine->getScene();
	renderingEngine->drawScene(scene, &entities);
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
                {renderingEngine->aConsole.propragateMsg("Number of elements in cars: " + renderingEngine->FloatToString(entities.cars.size()));}

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
    int rTriggMag = state->rTrigger / 60;
    int lTriggMag = state->lTrigger / 60;
    int torque = state->leftStick.x * (state->leftStick.magnitude/-5);

	NxVec3 v0 = NxVec3(rTriggMag*1000,0,0);
    NxVec3 v1 = NxVec3(lTriggMag*-1000,0,0);
    NxVec3 v2 = NxVec3(0,torque,0);
    //NxVec3 dir = NxVec3(state->leftStick.x,0,0);    
        
    entities.cars[0]->aWheel1->getActor().addLocalForce(v0);
    entities.cars[0]->aWheel1->getActor().addLocalForce(v1);
    entities.cars[0]->aWheel1->getActor().addTorque(v2);

    if (state->a)
    {
        if (!(entities.cars[0]->aWheel1 == NULL))
		{
            //cars[0]->aWheel1->getActor().setLinearVelocity(v3);
			//cars[0]->aWheel2->getActor().setLinearVelocity(v3);
			//cars[0]->aWheel2->getActor().addTorque(v3);
			//cars[0]->aWheel1->setAxleSpeed(1);
			//cars[0]->aWheel2->setAxleSpeed(1);
		}	
        else
            printf("NULL WHEEL0 at Cars[0]\n");
    }


    //if (state->b)
    //{
    //    if (!(entities.cars.at(0)->aWheel1 ==NULL))
    //    {entities.cars.at(0)->aWheel1->getActor().addForce(v3);}
    //    else
    //    {printf("NULL WHEEL0 at Cars[0]\n");}
    //}
    //if (state->x)
    //{
    //    if (!(entities.cars.at(0)->components.at(0) == NULL))
    //    {entities.cars.at(0)->components.at(0)->getActor()->addForce(v3);}
    //    else
    //    {printf("NULL Cars[0]\n");}
    //}
    //if (state->y)
    //{
    //    if (!(entities.cars.at(0)->components.at(0) == NULL))
    //    {entities.cars.at(0)->components.at(0)->getActor()->moveGlobalPosition(v0);}
    //    else
    //    {printf("NULL Cars[0]\n");}
    //}

    //cars.at(0)->aWheel1->setMotorTorque(trig);
    //cars.at(0)->aWheel1->setAxleSpeed(trig);
    //cars.at(0)->aWheel->motorTorque.setMotorTorque(trig);
	if(state->lb) {
		physicsEngine->resetBox();
        entities.cars[0]->components[0]->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));
	}
}

PlayState* PlayState::getInstance()
{    
    printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}