#include "PlayState.h"


PlayState::PlayState()
{
    changeState(PLAY);    
    entities.cars.push_back(new Entity);
    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
	renderingEngine->initializeGL();

    ObjModel* aModel = renderingEngine->getModelManger().getModel(2);
    physicsEngine->createTriMesh(0,-0.5f,0,*aModel);
    physicsEngine->createBoxes(-103.811f, 0.403f, -292.283f, 5, 2.5f);
    physicsEngine->createBoxes(-11.138f, 4.188f, -320.407f, 5, 2.5f);
    physicsEngine->createBoxes(-360.586f, 0.407f, -326.88f, 5, 2.5f);
    physicsEngine->createBoxes(-675.201f, 0.403f, -325.229f, 5, 2.5f);
    physicsEngine->createBoxes(-319.045f, 157.17f, 698.045f, 5, 2.5f);


    //2
    physicsEngine->createStaticBox(-4.195f, 0.403f, -200.2202f);
    physicsEngine->createStaticBox(-404.991f, 4.188f, -320.407f);

    InitializeConsoleCommands();    //Initalize Commands
}

void PlayState::update(float dt)
{    
    physicsEngine->step(dt/1000);
    
//    entities.cars[0]->aCam->updateCamera(dt/16);
    entities.cars[0]->aCam->updateCamera(1.0f);
}

void PlayState::render()
{    	    
	NxScene* scene = physicsEngine->getScene();
	renderingEngine->drawScene(scene, &entities);
}



//Console Commands, you should make sure that this has been linked to the console, via InitializeConsoleCommands
void PlayState::InitializeConsoleCommands()
{
   // renderingEngine->aConsole.commands["foo"] = foo;
}

int foo(int a) {
    std::cout << "foo executed " << a << std::endl;
    return 0;
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
                //if (renderingEngine->aConsole.commands has command
  //              if (renderingEngine->aConsole.commands.find(renderingEngine->aConsole.consoleString) ==renderingEngine->aConsole.commands.end() )
 //               {renderingEngine->aConsole.commands[renderingEngine->aConsole.consoleString](0);}


                if (renderingEngine->aConsole.consoleString == "off g")
                {
                    physicsEngine->getScene()->setGravity(NxVec3(0,0,0));
                }
                if (renderingEngine->aConsole.consoleString == "on g")
                {
                    physicsEngine->getScene()->setGravity(NxVec3(0,-9.81f,0));
                }

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

                if (renderingEngine->aConsole.consoleString == "tog text0")
                {
                    glBindTexture(GL_TEXTURE_2D, renderingEngine->textureid_P1[0]);
                }
                if (renderingEngine->aConsole.consoleString == "tog text1")
                {
                    glBindTexture(GL_TEXTURE_2D, renderingEngine->textureid_P1[1]);
                }
                if (renderingEngine->aConsole.consoleString == "tog text2")
                {
                    glBindTexture(GL_TEXTURE_2D, renderingEngine->textureid_P1[2]);
                }
                if (renderingEngine->aConsole.consoleString == "tog text3")
                {
                    glBindTexture(GL_TEXTURE_2D, renderingEngine->textureid_P1[3]);
                }
                


                if (renderingEngine->aConsole.consoleString == "get curloc")
                {
                    entities.cars.at(0)->getActor()->getGlobalPose().t;
                    renderingEngine->aConsole.propragateMsg(
                        "CurrentLocation: X:" +
                        renderingEngine->FloatToString(entities.cars.at(0)->getActor()->getGlobalPose().t.x) + 
                        "CurrentLocation: Y:" +
                        renderingEngine->FloatToString(entities.cars.at(0)->getActor()->getGlobalPose().t.y) + 
                        "CurrentLocation: Z:" +
                        renderingEngine->FloatToString(entities.cars.at(0)->getActor()->getGlobalPose().t.z)
                        );
                }

                //set Commands

                if (renderingEngine->aConsole.consoleString == "spawn obstacles")
                {
                    for (int x=0;x<20;x++)
                    {

                        float newX = (rand() % 40) - 20.0f;//rand() + 1;
                        float newZ = (rand() % 40) - 20.0f;//rand() + 1;

                        printf ("CreateBox: %f, %f, %f\n", newX, 3.5f, newZ );

                        NxActor* aBox = physicsEngine->createBox(
                                                                    newX,
                                                                    3.5f,
                                                                    newZ
                                                                    
                                                                   // 0,
                                                                   // 3.5f,
                                                                   // 0
                                                                    );
                        Entity aEntity;
                        //EntityComponent aEC;
                        aEntity.setActor(aBox);
                        //aEntity.addComponent(&aEC);
                        entities.Obstacles.push_back(&aEntity);
                    }
                     renderingEngine->aConsole.propragateMsg("Created 20 Boxes");
                }

                if (renderingEngine->aConsole.consoleString == "spawn static obs")
                {
                    for (int x=0;x<20;x++)
                    {

                        float newX = (rand() % 40) - 20.0f;//rand() + 1;
                        float newZ = (rand() % 40) - 20.0f;//rand() + 1;


                        NxActor* aBox = physicsEngine->createStaticBox(
                                                                    newX,
                                                                    -0.05f,
                                                                    newZ
                                                                    
                                                                   // 0,
                                                                   // 3.5f,
                                                                   // 0
                                                                    );
                        Entity aEntity;
                        //EntityComponent aEC;
                        aEntity.setActor(aBox);
                        //aEntity.addComponent(&aEC);
                        entities.Obstacles.push_back(&aEntity);
                    }
                     renderingEngine->aConsole.propragateMsg("Created 20 static Boxes");
                }
                if (renderingEngine->aConsole.consoleString == "spawn saruk")
                {
                    //for (int x=0;x<20;x++)
                    {
                        
                        ObjModel* aModel = renderingEngine->getModelManger().getModel(1);
                        physicsEngine->createTriMesh(0, 0, 0, 
                                                    *aModel
                                                    );
                    }
                     renderingEngine->aConsole.propragateMsg("Created Saruk");
                }
                if (renderingEngine->aConsole.consoleString == "spawn track")
                {
                    //for (int x=0;x<20;x++)
                    {
                        
                        ObjModel* aModel = renderingEngine->getModelManger().getModel(2);
                        physicsEngine->createTriMesh(0, 0, 0, 
                                                    *aModel
                                                    );
                    }
                     renderingEngine->aConsole.propragateMsg("Created track");
                }
                if (renderingEngine->aConsole.consoleString == "reset car")
                {
                    physicsEngine->resetBox();
                    entities.cars[0]->getActor()->setGlobalPosition(NxVec3(0,35.0f,0));
                    entities.cars[0]->getActor()->setGlobalOrientation(NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1)));
                     renderingEngine->aConsole.propragateMsg("Car Reset");
                }
                
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
    float m = 0;
    float d = 0;
    //UserCamControl   
    entities.cars[0]->aCam->updateCamera(1.0f);
    entities.cars[0]->aCam->setUserCamControl(NxVec3 (state->rightStick.y, 0, state->rightStick.x));
        
    int rTriggMag = state->rTrigger;
    int lTriggMag = state->lTrigger;
    int torque = state->leftStick.x * (state->leftStick.magnitude/-5);

	if(rTriggMag > 0)
        entities.cars[0]->addTorque(rTriggMag);        
	if(lTriggMag > 0)
        entities.cars[0]->addTorque(-1*lTriggMag);        

 //   m = -(physicsEngine->w1->getSteerAngle());    //get the value under 1
 //   d = 0.1f * m;

 //   if (rTriggMag == 0 && lTriggMag == 0)
	//{
	//	physicsEngine->losing();
	//}

    //entities.cars[0]->addSteeringAngle(d);
    //physicsEngine->w1->setSteerAngle( (physicsEngine->w1->getSteerAngle() + d) );

	if(torque > 0)
	{
        m = state->leftStick.magnitude / 24000.0f;    //get the value under 1
        d = 0.05f * m;
        entities.cars[0]->addSteeringAngle(d);
	}
	else if(torque < 0)
	{
        m = state->leftStick.magnitude / 24000.0f;    //get the value under 1
        d = 0.05f * m;
        entities.cars[0]->addSteeringAngle(d*-1);
	}

	if(state->lb) {
		physicsEngine->resetBox();
        entities.cars[0]->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));
        entities.cars[0]->getActor()->setGlobalOrientation(NxMat33(NxVec3(1,0,0),NxVec3(0,1,0),NxVec3(0,0,1)));
	}
}

PlayState* PlayState::getInstance()
{    
    printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}