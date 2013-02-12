#include "PlayState.h"

float deg = 0.1;

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
<<<<<<< HEAD:mPULSE Project/mPULSE/GameStates/PlayState.cpp
    physicsEngine->createBoxes(-103.811f, 0.410f, -292.283f, 10, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-11.138f, 4.198f, -320.407f, 10, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-360.586f, 0.417f, -326.88f, 10, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-675.201f, 0.413f, -325.229f, 10, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-319.045f, 157.18f, 698.045f, 10, 2.5f, &entities.Obstacles);
=======
    physicsEngine->createBoxes(-103.811f, 0.403f, -292.283f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-11.138f, 4.188f, -320.407f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-360.586f, 0.407f, -326.88f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-675.201f, 0.403f, -325.229f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-319.045f, 157.17f, 698.045f, 5, 2.5f, &entities.Obstacles);
>>>>>>> 513157ee208f3dae4c99facfeb90e4472fd9237b:mPULSE/mPULSE/GameStates/PlayState.cpp


    //2
    Entity aEntity;
    aEntity.setActor(physicsEngine->createStaticBox(-4.195f, 0.403f, -200.2202f));
    Entity aEntity2;
    aEntity.setActor(physicsEngine->createStaticBox(-404.991f, 4.188f, -320.407f));
    entities.StaticObjs.push_back(&aEntity);
    entities.StaticObjs.push_back(&aEntity2);

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

                if (renderingEngine->aConsole.consoleString == "num entities")
                {
                    renderingEngine->aConsole.propragateMsg("Number of elements in cars: " + renderingEngine->FloatToString(entities.cars.size()));
                    renderingEngine->aConsole.propragateMsg("Number of elements in AIcars: " + renderingEngine->FloatToString(entities.AIcars.size()));
                    renderingEngine->aConsole.propragateMsg("Number of elements in Obstacles: " + renderingEngine->FloatToString(entities.Obstacles.size()));
                    renderingEngine->aConsole.propragateMsg("Number of elements in StaticObj: " + renderingEngine->FloatToString(entities.StaticObjs.size()));
                    renderingEngine->aConsole.propragateMsg("Number of elements in Track: " + renderingEngine->FloatToString(entities.Track.size()));
                }

                if (renderingEngine->aConsole.consoleString == "num actors")
                {renderingEngine->aConsole.propragateMsg("Number of actors in scene: " + renderingEngine->FloatToString(physicsEngine->getScene()->getNbActors()));}

                if (renderingEngine->aConsole.consoleString == "num debugphysic")
                {
                    renderingEngine->aConsole.propragateMsg("Number of Lines in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbLines()));
                    renderingEngine->aConsole.propragateMsg("Number of Points in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbPoints()));
                    renderingEngine->aConsole.propragateMsg("Number of Triangles in debug physic: " + renderingEngine->FloatToString(physicsEngine->getScene()->getDebugRenderable()->getNbTriangles()));
                }
                
                if(renderingEngine->aConsole.consoleString == "a")
                {
                    deg+=0.1;
                    renderingEngine->aConsole.propragateMsg(renderingEngine->FloatToString(deg));
                }
                if(renderingEngine->aConsole.consoleString == "b")
                {
                    deg-=0.1;
                    renderingEngine->aConsole.propragateMsg(renderingEngine->FloatToString(deg));
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
                        NxActor* aTri = physicsEngine->createTriMesh(0, 0, 0, 
                                                    *aModel
                                                    );
                        Entity aEntity;
                        aEntity.setActor(aTri);
                        aEntity.setModel(aModel);
                        entities.Track.push_back(&aEntity);
                    }
                     renderingEngine->aConsole.propragateMsg("Created Saruk");
                }
                if (renderingEngine->aConsole.consoleString == "spawn track")
                {
                    //for (int x=0;x<20;x++)
                    {
                        
                        ObjModel* aModel = renderingEngine->getModelManger().getModel(2);
                        NxActor* aTri = physicsEngine->createTriMesh(0, 0, 0, 
                                                    *aModel
                                                    );
                        Entity aEntity;
                        aEntity.setActor(aTri);
                        aEntity.setModel(aModel);
                        entities.Track.push_back(&aEntity);
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
    //state->vibrate(((float)state->rTrigger/(float)state->MAX_TRIGGER_MAG)*(float)state->MAX_VIB,((float)state->rTrigger/(float)state->MAX_TRIGGER_MAG)*(float)state->MAX_VIB);

    if(player < entities.cars.size())
    {
        //UserCamControl  
        Entity* car = entities.cars[player];
        car->aCam->updateCamera(1.0f);
        car->aCam->setUserCamControl(NxVec3 (state->rightStick.y, 0, state->rightStick.x));
    
        NxVec3 a = car->getActor()->getLinearVelocity();
        //printf("x: %f y: %f z: %f \n",a.x,a.y,a.z);
        int rTriggMag = state->rTrigger;
        int lTriggMag = state->lTrigger;    
        static int count = 0;

        car->addTorque(rTriggMag - lTriggMag);        
        car->addSteeringAngle((state->leftStick.magnitude) * -state->leftStick.x / 24000.0f);

        //printf("mag: %f x: %f ang: %f\n",state->leftStick.magnitude,state->leftStick.x,(state->leftStick.magnitude/24000.0) * -state->leftStick.x * deg);


        if(state->b)
            car->brake(5000);
        else
            car->brake(0);

        if(state->lb) {
		    physicsEngine->resetBox();
                NxQuat q;
                q.fromAngleAxis(90, NxVec3(0,1,0));
                NxMat33 orient;
                orient.fromQuat(q);

            car->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));
            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
	    }
    }
}

PlayState* PlayState::getInstance()
{    
     printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}