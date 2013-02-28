#include "PlayState.h"

PlayState::PlayState()
{
    showConsole = true;
    rbPressed = false;
    changeState(PLAY); 

    Entity* playerCar = new Entity();
    entities.cars.push_back(playerCar);

    RenderableComponent* pc_rc = new RenderableComponent(1,3);
    playerCar->rc.push_back(pc_rc);
    
    int num_AI = 2;

    for (int a=0;a<num_AI;a++)
    {

        Entity* newAIrCar = new Entity();
        RenderableComponent* newRc = new RenderableComponent(1, 5);
        newAIrCar->rc.push_back(newRc);
        entities.cars.push_back(newAIrCar);

    }    
    
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
    renderingEngine->setPlayerNum(gameVariables->getPlayerNum());

    //set numPlayers
	//renderingEngine->initializeGL();
    renderingEngine->createLight();

    //Create Track        
    Entity* aTrack = new Entity();
    ObjModel* aModel = renderingEngine->getModelManger().getModel("Race1.obj");
    RenderableComponent* rc = new RenderableComponent(2,7);    

    if(aModel != NULL)
    {
        aTrack->setActor(physicsEngine->createTriMesh(0,-0.5f,0,*aModel));
        entities.Track.push_back(aTrack);
        aTrack->rc.push_back(rc);        
        aTrack->setDisplayListIndex(renderingEngine->generateDisplayList("Race1.obj",0,0,0,1));     
    }   
    track = new Track("Race1.txt",aTrack);
    //*/

    physicsEngine->createBoxes(-103.811f, 0.403f, -292.283f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-11.138f, 4.188f, -320.407f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-360.586f, 0.407f, -326.88f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-675.201f, 0.403f, -325.229f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-319.045f, 157.17f, 698.045f, 5, 2.5f, &entities.Obstacles);

	soundEngine = SoundEngine::getInstance();
	soundEngine->initializeSound();
	soundEngine->toggleMusic();

    //2
    Entity* aEntity = new Entity();
    aEntity->setActor(physicsEngine->createStaticBox(-4.195f, 0.403f, -200.2202f));
    Entity* aEntity2 = new Entity();
    aEntity2->setActor(physicsEngine->createStaticBox(-404.991f, 4.188f, -320.407f));
    RenderableComponent* rc2 = new RenderableComponent(0,5);
    aEntity->rc.push_back(rc2);
    aEntity2->rc.push_back(rc2);
    entities.StaticObjs.push_back(aEntity);
    entities.StaticObjs.push_back(aEntity2);

    InitializeConsoleCommands();    //Initalize Commands
}

void PlayState::update(float dt)
{    
    //Raycasting code    
    /*NxScene* scene = physicsEngine->getScene(); 
    NxRay ray;
    NxRaycastHit hit;
    ray.orig = entities.cars[0]->getActor()->getGlobalPosition();
    ray.dir = entities.cars[0]->getActor()->getLinearVelocity(); //Need to normalize?
    scene->raycastClosestShape(ray,NX_ALL_SHAPES,hit);
    NxVec3 result = hit.worldImpact - ray.orig;
    */
    physicsEngine->step(dt/1000);
    /*
    NxVec3 result2 = hit.worldImpact - entities.cars[0]->getActor()->getGlobalPosition();
    if(result.dot(result2) < 0)
        printf("fallin!");*/

    entities.cars[0]->aCam->updateCamera(1.0f);
    entities.cars[1]->aCam->updateCamera(1.0f);

    for (unsigned c = 0; c < entities.cars.size(); ++c)
    {
        Entity* car = entities.cars[c];
        if (car->getActor()->getGlobalPose().t.y < -2.0f)
        {
            car->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));

            NxVec3 v(0,1,0);
            NxReal ang = 90;

            NxQuat q;
            q.fromAngleAxis(ang, v);
            NxMat33 orient;
            orient.fromQuat(q);

            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
            car->aCam->resetCamera();
        }
    }

    for (unsigned c = 0; c < entities.AIcars.size(); ++c)
    {
        Entity* car = entities.AIcars[c];
        if (car->getActor()->getGlobalPose().t.y < -2.0f)
        {
            car->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));

            NxVec3 v(0,1,0);
            NxReal ang = 90;

            NxQuat q;
            q.fromAngleAxis(ang, v);
            NxMat33 orient;
            orient.fromQuat(q);

            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
            car->aCam->resetCamera();
        }
    }

    
//    entities.cars[0]->aCam->updateCamera(dt/16);
    //entities.cars[0]->aCam->updateCamera(1.0f);
}

void PlayState::render()
{    	    
	NxScene* scene = physicsEngine->getScene();
	renderingEngine->drawScene(scene, track, &entities);
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
    if (showConsole)
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
                
                //Get Commands
                //if (renderingEngine->aConsole.consoleString == "get testwheel")
                //{renderingEngine->aConsole.consoleString = "Test Wheel Torgue: " + renderingEngine->FloatToString(cars.at(0)->aWheel1->getMotorTorque());renderingEngine->aConsole.propragateMsg();}

                //tog Commands
                if ((renderingEngine->aConsole.consoleString == "tog debugphysic") || (renderingEngine->aConsole.consoleString == "tog dp"))
                {
                    if (renderingEngine->debugPhysX){renderingEngine->debugPhysX=false;renderingEngine->showScene=true;}else{renderingEngine->debugPhysX=true;renderingEngine->showScene=false;}; 
                }
                if ((renderingEngine->aConsole.consoleString == "tog camera") || (renderingEngine->aConsole.consoleString == "tog c"))
                {
                    if (renderingEngine->debugCamera){renderingEngine->debugCamera=false;}else{renderingEngine->debugCamera=true;}; 
                    renderingEngine->aConsole.propragateMsg("toggled Camera Debug");
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
                        Entity* aEntity = new Entity;
                        //EntityComponent aEC;
                        aEntity->setActor(aBox);
                        RenderableComponent* rc = new RenderableComponent(0,6);
                        aEntity->rc.push_back(rc);
                        //aEntity.addComponent(&aEC);
                        entities.Obstacles.push_back(aEntity);
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
                        Entity* aEntity = new Entity;
                        aEntity->setActor(aBox);
                        RenderableComponent* rc = new RenderableComponent(0,6);
                        aEntity->rc.push_back(rc);
                        entities.Obstacles.push_back(aEntity);
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
                        RenderableComponent* nexRc = new RenderableComponent(1,1);
                        //aEntity.rc.push_back(&nexRc);                                   //I LEAVFT OFF HERE
                        aEntity.rc.push_back(nexRc);
                        //aEntity.setModel(aModel);
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
                        RenderableComponent* rc = new RenderableComponent(2,2);
                        aEntity.rc.push_back(rc);
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
    }


    //Non-Console
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if (keyPressed == SDLK_F1)
            {if (showConsole){showConsole=false;}else{showConsole=true;}}

            else if (keyPressed == SDLK_a)
            {
                Entity* car = entities.cars[0];
                car->addSteeringAngle(500.0f);
            }
            else if (keyPressed == SDLK_d)
            {
                Entity* car = entities.cars[0];
                car->addSteeringAngle(-500.0f);
            }
            else if (keyPressed == SDLK_w)
            {
                Entity* car = entities.cars[0];
                car->addTorque(1000);
            }
            else if (keyPressed == SDLK_s)
            {
                Entity* car = entities.cars[0];
                car->addTorque(-1000);        
            }
        }


    return true;
}

void PlayState::handleXboxEvents(int player,XboxController* state)
{

    //logReplay(player, state, 0);      Used to log replay!

    //if (state->back)
    if (state->rb && !rbPressed)
    {
        logWayPoint(0);
        rbPressed = true;
        printf("Point logged pressed\n");
    }

    else if (!state->rb)
        rbPressed = false;    

    int carCount = entities.cars.size();
    if (player < carCount)
    {
        //UserCamControl  
        Entity* car = entities.cars[player];
        car->aCam->setUserCamControl(NxVec3 (state->rightStick.y, 0, state->rightStick.x));
    
        NxVec3 a = car->getActor()->getLinearVelocity();
        //printf("x: %f y: %f z: %f \n",a.x,a.y,a.z);
        int rTriggMag = state->rTrigger;
        int lTriggMag = state->lTrigger;    
        static int count = 0;

        car->addTorque(rTriggMag - lTriggMag);        
        car->addSteeringAngle((state->leftStick.magnitude) * -state->leftStick.x / 24000.0f);
//        car->addTilSteeringAngle((state->leftStick.magnitude) * -state->leftStick.x / 24000.0f);

        //printf("mag: %f x: %f ang: %f\n",state->leftStick.magnitude,state->leftStick.x,(state->leftStick.magnitude/24000.0) * -state->leftStick.x * deg);

		if(state->x)
			car->chargeBattery();
		if(state->y)
			car->dischargeBattery();
        if(state->b)
            car->brake(5000);
        else
            car->brake(0);   
        if(state->a)
            car->firePickup();

        if(state->lb) {
		    physicsEngine->resetBox();
            car->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));

            NxVec3 v(0,1,0);
            NxReal ang = 90;

            NxQuat q;
            q.fromAngleAxis(ang, v);
            NxMat33 orient;
            orient.fromQuat(q);

            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
            car->aCam->resetCamera();
	    }
    }
}


void PlayState::logReplay(int player, XboxController* state, float dt)
{
        int rTriggMag = state->rTrigger;
        int lTriggMag = state->lTrigger;    
        float leftStickMag = state->leftStick.magnitude;
        float LeftStickX = state->leftStick.x;
        float LeftStickY = state->leftStick.y;



        std::ofstream out;
        out.open( "replay.txt", std::ios_base::app );
        if( !out )
        {
           printf( "Couldn't open file.\n");
        }
        else
        {
           out << "dt " + renderingEngine->FloatToString(dt) + char(10) + char(13);
           out << "----------------------------------------------------------------" + char(10) + char(13);
           out << "PLAYER: " + renderingEngine->FloatToString(player) + char(10) + char(13);
           out << "rTigMag " + renderingEngine->FloatToString(rTriggMag) + char(10) + char(13);
           out << "lTigMag " + renderingEngine->FloatToString(lTriggMag) + char(10) + char(13);
           out << "lStickMag " + renderingEngine->FloatToString(leftStickMag) + char(10) + char(13);
           out << "lStickX " + renderingEngine->FloatToString(LeftStickX) + char(10) + char(13);
           out << "lStickY " + renderingEngine->FloatToString(LeftStickY) + char(10) + char(13);
           out << char(10);
           out << char(13);
           out << char(10);
           out << char(13);
        }
        out.close();
}

void PlayState::logWayPoint(int player)
{


    Entity* car = entities.cars[player];
    
    NxVec3 loc = car->getActor()->getGlobalPose().t;
    NxMat33 ori = car->getActor()->getGlobalOrientation();

    NxVec3 spd = car->getActor()->getLinearVelocity();
    float spdF = car->getActor()->getLinearVelocity().magnitude();

    float brk0 = car->getDriveWheels().at(0)->getBrakeTorque();
    float brk1 = car->getDriveWheels().at(1)->getBrakeTorque();

        std::ofstream out;
        out.open( "replay.txt", std::ios_base::app );
        if( !out )
        {
           printf( "Couldn't open file.\n");
        }
        else
        {
           out << "WAYPOINT" + char(10) + char(13);
           out << "loc: " + renderingEngine->FloatToString(loc.x) + " " + renderingEngine->FloatToString(loc.y) + " " + renderingEngine->FloatToString(loc.z) + char(10) + char(13);
           out << "ori0: " + renderingEngine->FloatToString(ori.getRow(0).x) + " " + renderingEngine->FloatToString(ori.getRow(0).y) + " " + renderingEngine->FloatToString(ori.getRow(0).z) + char(10) + char(13);
           out << "ori1: " + renderingEngine->FloatToString(ori.getRow(1).x) + " " + renderingEngine->FloatToString(ori.getRow(1).y) + " " + renderingEngine->FloatToString(ori.getRow(1).z) + char(10) + char(13);
           out << "ori2: " + renderingEngine->FloatToString(ori.getRow(2).x) + " " + renderingEngine->FloatToString(ori.getRow(2).y) + " " + renderingEngine->FloatToString(ori.getRow(2).z) + char(10) + char(13);
           //out << "spd: " + renderingEngine->FloatToString(spd.x) + " " + renderingEngine->FloatToString(spd.y) + " " + renderingEngine->FloatToString(spd.z) + char(10) + char(13);
           out << "spd: " + renderingEngine->FloatToString(spdF) + char(10) + char(13);
           out << "brk0: " + renderingEngine->FloatToString(brk0) + char(10) + char(13);
           out << "brk1: " + renderingEngine->FloatToString(brk1) + char(10) + char(13);
           out << char(10);
           out << char(13);
        }
        out.close();
}



PlayState* PlayState::getInstance()
{    
     printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}