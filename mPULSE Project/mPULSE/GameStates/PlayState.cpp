#include <GameStates/PlayState.h>

PlayState::PlayState()
{
    resetAll();
    quit = false;
}

void PlayState::resetAll()
{
    raceStartTime = 0;
    pauseTime = 0; 
    maxPauseTime = 300;
    eventManager = EventManager::getInstance();
    gameVariables = GameVariables::getInstance();
    keyAPressed = false;
    keyDPressed = false;
    keyWPressed = false;
    keySPressed = false;
    paused = false;

    id = 0;
    showConsole = true;
    rbPressed = false;

    CHEAT_InfPowUp = false;
    CHEAT_InfBoost = false;

    gameVariables->resetRace();     //Clears victory flags
    gameVariables->finishTime = NULL;
    entities.clearAll();

    time.reset();

    changeState(PLAY); 
    numPlayers = gameVariables->getNumPlayers();
    int num_AI = gameVariables->numberOfAIs;

    rankings = new std::vector<Entity*>;
    for(int i=0;i<numPlayers;i++)
    {
        Entity* playerCar = new Entity();
        playerCar->rankingName = gameVariables->getPlayerProfile(i)->data.driverName;
        playerCar->aAI = new AI();
        rankings->push_back(playerCar);
        entities.cars.push_back(playerCar);

        //RenderableComponent* pc_rc = new RenderableComponent(1,3);      //need to read from profile
        RenderableComponent* pc_rc = new RenderableComponent(gameVariables->getPlayerProfile(i)->data.carModel,gameVariables->getPlayerProfile(i)->data.carTexture);      //need to read from profile
        playerCar->rc.push_back(pc_rc);
    }   
    for (int a=0;a<num_AI;a++)
    {
        int AIType = rand() % 4;

        //AIType = 2;

        Entity* newAIrCar = new Entity();
        RenderableComponent* newRc;
        newAIrCar->aAI = new AI();
        rankings->push_back(newAIrCar);

        AI_Names* aiNames = AI_Names::getInstance();

        switch (AIType)
        {
        case 0:
            newRc = new RenderableComponent(1, 0);
            newAIrCar->aAI->myPersonality.setPersonality(AIType);
            newAIrCar->rankingName = aiNames->getRandomName();
            break;

        case 1:
            newRc = new RenderableComponent(1, 4);
            newAIrCar->aAI->myPersonality.setPersonality(AIType);
            newAIrCar->rankingName = aiNames->getRandomName();
            break;

        case 2:
            newRc = new RenderableComponent(11, 5);
            newAIrCar->aAI->myPersonality.setPersonality(AIType);
            newAIrCar->rankingName = aiNames->getAngryName();
            break;

        case 3:
            newRc = new RenderableComponent(1, 6);
            newAIrCar->aAI->myPersonality.setPersonality(AIType);
            newAIrCar->rankingName = aiNames->getRandomName();
            break;
        
        default:
            newRc = new RenderableComponent(1, 5);
            newAIrCar->aAI->myPersonality.setPersonality(AIType);
            newAIrCar->rankingName = aiNames->getRandomName();
            break;

        }

        newAIrCar->rc.push_back(newRc);
        //entities.cars.push_back(newAIrCar);
        entities.AIcars.push_back(newAIrCar);

    }
    
    //*/
        
    physicsEngine = PhysicsEngine::getInstance();
    physicsEngine->setupPlayScene(&entities.cars);  //Assign actors to the entities
    physicsEngine->setupCars(&entities.AIcars);  //Assign actors to the entities without the initalization of the engine

    renderingEngine = RenderingEngine::getInstance();

    //set numPlayers
    renderingEngine->createLight();





    
        /*//UNDER CONSTUCTION CODE//
        Entity* aTrack = new Entity();

    Track* tempTrackReader = new Track(".\\InGameObjects\\Race1.txt",aTrack);
    std::string trackFilename = gameVariables->loadedTracks->getTrackFilename(gameVariables->selectedTrack);
    tempTrackReader->loadTrackAdditions(trackFilename);
    int physXModelNum = tempTrackReader->infoz.physics;

    //gameVariables->loadedTracks->getTrackFilename(gameVariables->selectedTrack)
    ObjModel* aModel = renderingEngine->getModelManger().getModel(physXModelNum);
    RenderableComponent* rc = new RenderableComponent(physXModelNum,7);

    if(aModel != NULL)
    {
        aTrack->setActor(physicsEngine->createTriMesh(0,-0.5f,0,*aModel));
        entities.Track.push_back(aTrack);
        aTrack->rc.push_back(rc);        
        //aTrack->setDisplayListIndex(renderingEngine->generateDisplayList("Race1.obj",0,0,0,1));    
        aTrack->setDisplayListIndex(renderingEngine->generateDisplayList("Race1.obj",0,0,0,1)); 
    }   
    track = new Track(trackFilename,aTrack);
	physicsEngine->createWaypoints(track->getWaypoints());
    *//////////////////////////////////


    ///THIS IS A HACK FOR MILESTONE 4
    
    Entity* aTrack;
    ObjModel* aModel;
    
    
    //int st = gameVariables->theSelectedTrack->infoz.physics;
    if (gameVariables->isLoaded == false)
    {
        //If Track is not loaded from stageSelect, use default variables. Hopefully they still work!
        printf("PlayState: Track doesn't seem to have been loaded, attempting to compensate by using pre-determined variables/n");
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
        track = new Track(".\\InGameObjects\\Race1.txt",aTrack);
	    physicsEngine->createWaypoints(track->getWaypoints());
    }
    else
    {
        //Create Track from variables in gameVariables
        aTrack = new Entity();
        aModel = renderingEngine->getModelManger().getModel(gameVariables->theSelectedTrack->infoz.physics);

                if(aModel != NULL)
                {
                    //aTrack->setActor(physicsEngine->createTriMesh(0,0.0f,0,*aModel));
                    aTrack->setActor(physicsEngine->createTriMesh(0,0.0f,0,*aModel));
                    entities.Track.push_back(aTrack);

                    for each (RenderableComponent* rc in gameVariables->theSelectedTrack->infoz.pairs)
                    {
                        RenderableComponent* newRC = new RenderableComponent(rc->modelID, rc->textureID);
                        aTrack->rc.push_back(newRC);
                    }
                    //aTrack->rc = gameVariables->rcTrack;
                
                    printf("PlayState: Num of RC:%i\n", aTrack->rc.size());


                    aTrack->setDisplayListIndex(renderingEngine->generateDisplayList(aModel,0,0,0,1));     
                }   
                track = gameVariables->theSelectedTrack;
                track->setEntity(aTrack);
	            physicsEngine->createWaypoints(track->getWaypoints());
    }

    /*
    switch (gameVariables->selectedTrack)
    {
    case 1:
            aTrack = new Entity();
            aModel = renderingEngine->getModelManger().getModel(13);
            rc = new RenderableComponent(13,7);

            if(aModel != NULL)
            {
                aTrack->setActor(physicsEngine->createTriMesh(0,0.0f,0,*aModel));
                entities.Track.push_back(aTrack);
                aTrack->rc.push_back(rc);        
                aTrack->setDisplayListIndex(renderingEngine->generateDisplayList("Race1_Spiral.obj",0,0,0,1));     
            }   
            track = new Track(".\\InGameObjects\\Race_Spiral.txt",aTrack);
	        physicsEngine->createWaypoints(track->getWaypoints());
        break;

    default:
            aTrack = new Entity();
            aModel = renderingEngine->getModelManger().getModel("Race1.obj");
            rc = new RenderableComponent(2,7);

            if(aModel != NULL)
            {
                aTrack->setActor(physicsEngine->createTriMesh(0,0.0f,0,*aModel));
                entities.Track.push_back(aTrack);
                aTrack->rc.push_back(rc);        
                aTrack->setDisplayListIndex(renderingEngine->generateDisplayList("Race1.obj",0,0,0,1));     
            }   
            track = new Track(".\\InGameObjects\\Race1.txt",aTrack);
	        physicsEngine->createWaypoints(track->getWaypoints());
        break;

    }
    */

    //This is our old code to load in tracks
    /*
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
    track = new Track(".\\InGameObjects\\Race1.txt",aTrack);
	physicsEngine->createWaypoints(track->getWaypoints());
    */

    //Attach AI to the player cars
    for (unsigned pcai = 0; pcai < entities.cars.size();++pcai)
    {
        entities.cars[pcai]->aAI->setActor(entities.cars[pcai]->getActor());
    }

    //Attach AI to the cars
    for (unsigned aa = 0; aa < entities.AIcars.size(); ++aa)
    {
        entities.AIcars.at(aa)->aAI->setActor(entities.AIcars.at(aa)->getActor());   //Assign actors to the entities's AI   
        CustomData* customData = new CustomData(CustomData::CAR,-1,0,track->getFirst());
        entities.AIcars.at(aa)->setCustomData(customData);
    }
    //Attach customData to car actors
    for (unsigned a = 0; a < entities.cars.size(); ++a)
    {
        CustomData* customData = new CustomData(CustomData::CAR,-1,0,track->getFirst());
        entities.cars.at(a)->setCustomData(customData);
    }

    //*/

    physicsEngine->createBoxes(-103.811f, 0.403f, -292.283f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-11.138f, 4.188f, -320.407f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-360.586f, 0.407f, -326.88f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-675.201f, 0.403f, -325.229f, 5, 2.5f, &entities.Obstacles);
    physicsEngine->createBoxes(-319.045f, 157.17f, 698.045f, 5, 2.5f, &entities.Obstacles);

	soundEngine = SoundEngine::getInstance();
	soundEngine->initializeSound();
    soundEngine->stopMusic();
	//soundEngine->toggleMusic();
	soundEngine->startMusic(2);
    soundEngine->engineNoise();
    soundEngine->engineVol(1, 0);
    soundEngine->engineVol(2, 0);

    //2
    /*
    Entity* aEntity = new Entity();
    aEntity->setActor(physicsEngine->createStaticBox(-4.195f, 0.403f, -200.2202f));
    Entity* aEntity2 = new Entity();
    aEntity2->setActor(physicsEngine->createStaticBox(-404.991f, 4.188f, -320.407f));
    RenderableComponent* rc2 = new RenderableComponent(0,5);
    aEntity->rc.push_back(rc2);
    aEntity2->rc.push_back(rc2);
    entities.StaticObjs.push_back(aEntity);
    entities.StaticObjs.push_back(aEntity2);
    */
    renderingEngine->setEntities(&entities);
    InitializeConsoleCommands();    //Initalize Commands

    track;
    raceStarted = false;
    lastSecond = 0;
    initialTime = time.getCurrentTime()/1000;
    timeBeforeRaceStarts = 5;
    countdownTime = 2;
}

void PlayState::update(float dt)
{   
    unsigned curTime = time.getCurrentTime() / 1000;
    if(!raceStarted)
    {        
        if(curTime > timeBeforeRaceStarts + initialTime)
        {
            raceStarted = true;
            raceStartTime = time.getCurrentTime();
        }
        else if((curTime - initialTime > countdownTime))
        {            
            if(curTime != lastSecond)
                soundEngine->playSound(4, 8);

            renderingEngine->drawText(renderingEngine->FloatToString((timeBeforeRaceStarts - (curTime - initialTime) + 1)),-0.1,0,0.2);

            lastSecond = curTime;
        }
    }
    else if(raceStarted && (curTime < timeBeforeRaceStarts + initialTime + 2)) 
    {
        if(curTime != lastSecond)
            soundEngine->playSound(4, 10);

        renderingEngine->drawText("GO!",-0.2,0,0.2);

        lastSecond = curTime;
    }
    track;
    //renderingEngine->drawText(100, -100, renderingEngine->FloatToString(
    //printf("x: %f y: %f z: %f",entities.cars.at(0)->getActor()->getGlobalPosition().x)+" "+renderingEngine->FloatToString(entities.cars.at(0)->getActor()->getGlobalPosition().y)+" "+renderingEngine->FloatToString(entities.cars.at(0)->getActor()->getGlobalPosition().z);
    //Handle Events
    handleEvents();

    //deal with end of race
    calculateRankings();

    for (int playa=0;playa<gameVariables->getNumPlayers();playa++)
    {

        CustomData* cd = (CustomData*)entities.cars[playa]->getActor()->userData;

        if (cd->laps >= gameVariables->numLaps)
        {
            entities.cars[playa]->finishTime = time.getDeltaTime(raceStartTime);
            gameVariables->becomeFinished(playa);
            entities.cars[playa]->aCam->setMode(6);
        }

        //gameVariables->becomeFinished(playa);
    }

    if (gameVariables->getPlayerProfile(1)->data.isAI)
    {
        CustomData* cd = (CustomData*)entities.AIcars[0]->getActor()->userData;

        if (cd->laps > 1)
        {
            gameVariables->becomeFinished(1);
            entities.AIcars[0]->aCam->setMode(6);
        }
    }

    
    if (gameVariables->isFinishedRace())                    ///Finish Race here
    {
        const unsigned int FINISH_DELAY = 10000;
        if (gameVariables->finishTime == NULL)
        {
            gameVariables->finishTime = time.getCurrentTime();
            soundEngine->FadeOutMusic(4000);
            soundEngine->fadeOutAllSound(4000);
            renderingEngine->startFadeOut(FINISH_DELAY);
        }

        if (time.getDeltaTime(gameVariables->finishTime) >= FINISH_DELAY)
        {
            renderingEngine->resetFade();
            soundEngine->fadeOutAllSound(10); //make sure they really are off

            gameVariables->rankings.clear();
            for (unsigned e=0;e<rankings->size();e++)
            {
                gameVariables->addRanking(renderingEngine->FloatToString(rankings->at(e)->rank),rankings->at(e)->rankingName,renderingEngine->FloatToString(rankings->at(e)->finishTime));
            }

            changeState(RESULT);
        }
    }
    //

    //Handle all dead entities
    unsigned numOfObjs = entities.DynamicObjs.size();
    unsigned currObj = 0;

    while(currObj<numOfObjs)
    {    
        entities.DynamicObjs.at(currObj)->update();
        NxActor* a = entities.DynamicObjs.at(currObj)->getActor();
        if(!entities.DynamicObjs.at(currObj)->isAlive())
        {            
            numOfObjs--;
            physicsEngine->destroy(entities.DynamicObjs.at(currObj)->getActor());
            entities.DynamicObjs.erase(entities.DynamicObjs.begin()+currObj);
        }
        else
            currObj++;
    }

    //Keyboard Controls
            if (keyAPressed)
            {
                Entity* car = entities.cars[0];
                car->setSteeringAngle(1.0f);
            }
            else if (keyDPressed)
            {
                Entity* car = entities.cars[0];
                car->setSteeringAngle(-1.0f);
            }
            if (keySPressed)
            {
                Entity* car = entities.cars[0];
                car->addTorque(-255);
                car->addTorque(-255);
                car->addTorque(-255);
                car->addTorque(-255);
                car->addTorque(-255);
            }
            else if (keyWPressed)
            {
                Entity* car = entities.cars[0];
                car->addTorque(255);
                car->addTorque(255);
                car->addTorque(255);
                car->addTorque(255);
                car->addTorque(255);
            }

            //printf("KeyA: %i\n", keyAPressed);
            //printf("KeyD: %i\n", keyDPressed);
            //printf("KeyW: %i\n", keyWPressed);
            //printf("KeyS: %i\n", keySPressed);




    //soundengine p1
    float AxleSpeed = entities.cars.at(0)->getDriveWheels()->at(0)->getAxleSpeed();
    float vol = AxleSpeed * 0.75f;
    if (vol > 128){vol=128.0f;}
    soundEngine->engineVol(1, vol);
    if (AxleSpeed < 10)
        soundEngine->playSound(0,13);
    else if (AxleSpeed < 40)
        soundEngine->playSound(0,14);
    else if (AxleSpeed < 80)
        soundEngine->playSound(0,15);
    else if (AxleSpeed < 120)
        soundEngine->playSound(0,16);
    else if (AxleSpeed < 160)
        soundEngine->playSound(0,17);
    else if (AxleSpeed < 200)
        soundEngine->playSound(0,18);
    else if (AxleSpeed < 240)
        soundEngine->playSound(0,19);
    else if (AxleSpeed < 280)
        soundEngine->playSound(0,20);
    else if (AxleSpeed < 320)
        soundEngine->playSound(0,21);
    else if (AxleSpeed < 360)
        soundEngine->playSound(0,22);
    else
        soundEngine->playSound(0,23);

    entities.cars[0]->aCam->updateCamera(dt);
    if (entities.cars.size() > 1)
        entities.cars[1]->aCam->updateCamera(dt);

    for (unsigned c = 0; c < entities.cars.size(); ++c)
    {
		//Checking if any of the player cars have any sweep collisions.
        Entity* car = entities.cars[c];

        //Player car is being tracked. Play Alarm Sound.
        if(car->tracker != NULL)
            soundEngine->playSound(4,26);

        entities.cars[c]->aAI->update(entities.cars, entities.AIcars);
		NxSweepQueryHit* sweepResult = car->linearSweep(dt);
		car->setSweepCollision(false);
		if(sweepResult != NULL)
		{
			NxVec3 impactPoint = sweepResult->point;
			NxVec3 normal = sweepResult->normal;
			NxVec3 currPos = car->getActor()->getGlobalPose().t;

			NxVec3 testVec = impactPoint - currPos;
			NxReal dotResult = testVec.dot(normal);

			car->setSweepCollision(true);
			car->setImpactPoint(impactPoint);
			car->setImpactNormal(normal);
			car->setDotResult(dotResult);
			car->setOldVelocity(car->getActor()->getLinearVelocity());
			
			//printf("Sweep collision!\n");
		}
		
        
        car->update();
		
        if (car->getActor()->getGlobalPose().t.y < -20.0f)
        {
            //car->getActor()->setGlobalPosition(NxVec3(0,3.5f,0));
            CustomData* cd = (CustomData*)car->getActor()->userData;

            NxVec3 respawnPt = cd->wp->pos;
            //NxVec3 ori = cd->wp->ori;
            //float angle = acos(cd->wp->ori.dot(NxVec3(1,0,0)));

            car->getActor()->setGlobalPosition(respawnPt);
            //NxVec3 v(0,1,0);

            //NxQuat q;
            //q.fromAngleAxis(angle*(180.0f/3.14f), v);
			NxMat33 orient(cd->wp->ori);
            //orient.fromQuat(q);

            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
            car->aCam->resetCamera();
        }
    }

    for (unsigned c = 0; c < entities.AIcars.size(); ++c)
    {
        Entity* car = entities.AIcars[c];
        car->update();

        CustomData* cd = (CustomData*) car->getActor()->userData;
        if (cd->laps >= gameVariables->numLaps)
            car->finishTime = time.getDeltaTime(raceStartTime);

        //Do AI thinking here!!!!!
        //car->aAI->
        //car->aAI->setWaypoint(&Waypoint(7.83703,0.413632,-101.592));
        //car->aAI->setWaypoint(&Waypoint(entities.cars[0]->getActor()->getGlobalPose().t,,0,0));

        

        car->aAI->update(entities.cars, entities.AIcars);

		NxSweepQueryHit* sweepResult = car->linearSweep(dt);
		car->setSweepCollision(false);
		if(sweepResult != NULL)
		{
			NxVec3 impactPoint = sweepResult->point;
			NxVec3 normal = sweepResult->normal;
			NxVec3 currPos = car->getActor()->getGlobalPose().t;

			NxVec3 testVec = impactPoint - currPos;
			NxReal dotResult = testVec.dot(normal);

			car->setSweepCollision(true);
			car->setImpactPoint(impactPoint);
			car->setImpactNormal(normal);
			car->setDotResult(dotResult);
			car->setOldVelocity(car->getActor()->getLinearVelocity());
			
			//printf("AI Sweep collision!\n");
		}

        //Do AI Controller stuff
        handleXboxController(c, entities.AIcars ,entities.AIcars.at(c)->aAI->getControl(), false);
        //handleXboxController(0, entities.cars ,entities.AIcars.at(c)->aAI->getControl());


        if (car->getActor()->getGlobalPose().t.y < -20.0f)
        {
            CustomData* cd = (CustomData*)car->getActor()->userData;

            NxVec3 respawnPt = cd->wp->pos;
            //NxVec3 ori = cd->wp->ori;
            //float angle = acos(cd->wp->ori.dot(NxVec3(1,0,0)));
            car->getActor()->setGlobalPosition(respawnPt);
            
            //NxVec3 v(0,1,0);

            //NxQuat q;
            //q.fromAngleAxis(angle*(180.0f/3.14f), v);
			NxMat33 orient(cd->wp->ori);
            //orient.fromQuat(q);

            car->getActor()->setGlobalOrientation(orient);
            car->getActor()->setLinearVelocity(NxVec3(0,0,0));
            car->aCam->resetCamera();
        }
    }


        //Raycasting code    
    NxScene* scene = physicsEngine->getScene(); 
    NxRay ray;
    NxRaycastHit hit;
    ray.orig = entities.cars[0]->getActor()->getGlobalPosition();
    ray.dir = entities.cars[0]->getActor()->getLinearVelocity(); //Need to normalize?
    ray.dir.normalize();
    scene->raycastClosestShape(ray,NX_ALL_SHAPES,hit);
    NxVec3 result = hit.worldImpact - ray.orig;
    //*/
    //Display FPS
    renderingEngine->drawText("FPS: "+renderingEngine->FloatToString(1000.0f/dt),-0.95,0.85,0.03);
    //physicsEngine->step(dt/1000.0f);
    //physicsEngine->step(0.33f);
    //physicsEngine->step(1.0f/60.0f);
    if(!paused)
	    physicsEngine->step(dt/1000.0f);
    else
        renderingEngine->drawText("PAUSED",-0.1,0);

	
	for (unsigned c = 0; c < entities.cars.size(); ++c)
    {
		Entity* car = entities.cars[c];

		if(car->getSweepCollision())
		{
			NxVec3 impactPoint = car->getImpactPoint();
			NxVec3 normal = car->getImpactNormal();
			NxVec3 newPos = car->getActor()->getGlobalPose().t;

			NxVec3 testVec = impactPoint - newPos;
			NxReal dotResult = testVec.dot(normal);

			if((dotResult * car->getDotResult()) < 0)
			{
				//Dealing with player cars going through walls
				NxVec3 oldVelUnit = -car->getOldVelocity();
				oldVelUnit.normalize();
				normal.normalize();
				double angle = acos(oldVelUnit.dot(normal));

				double scale = car->getOldVelocity().magnitude() * cos(angle);
				NxVec3 scaledNormal = scale * normal;
				NxVec3 newVelVec = car->getOldVelocity() + (2.0f * scaledNormal);
				
				car->getActor()->setLinearVelocity(newVelVec*0.3); 
				newVelVec.normalize();
				NxVec3 newPos = car->getImpactPoint() + (newVelVec * 5.0f);
				car->getActor()->setGlobalPosition(newPos);

				printf("You definitely went through a wall.\n");
			}
		}
	}
	
	for (unsigned c = 0; c < entities.AIcars.size(); ++c)
    {
		Entity* car = entities.AIcars[c];

		if(car->getSweepCollision())
		{
			NxVec3 impactPoint = car->getImpactPoint();
			NxVec3 normal = car->getImpactNormal();
			NxVec3 newPos = car->getActor()->getGlobalPose().t;

			NxVec3 testVec = impactPoint - newPos;
			NxReal dotResult = testVec.dot(normal);

			if((dotResult * car->getDotResult()) < 0)
			{
				//Dealing with player cars going through walls
				NxVec3 oldVelUnit = -car->getOldVelocity();
				oldVelUnit.normalize();
				normal.normalize();
				double angle = acos(oldVelUnit.dot(normal));

				double scale = car->getOldVelocity().magnitude() * cos(angle);
				NxVec3 scaledNormal = scale * normal;
				NxVec3 newVelVec = car->getOldVelocity() + (2.0f * scaledNormal);
				
				car->getActor()->setLinearVelocity(newVelVec*0.3); 
				newVelVec.normalize();
				NxVec3 newPos = car->getImpactPoint() + (newVelVec * 5.0f);
				car->getActor()->setGlobalPosition(newPos);

				printf("AI definitely went through a wall.\n");
			}
		}
	}
	
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
                    physicsEngine->getScene()->releaseActor(entities.cars.at(1)->getPassiveWheels()->at(1)->getActor());
                }
                if (renderingEngine->aConsole.consoleString == "on g")
                {
                    physicsEngine->getScene()->setGravity(NxVec3(0,-9.81f,0));
                }

                if (renderingEngine->aConsole.consoleString == "cheat char")
                {
                    CHEAT_InfPowUp = true;
                    renderingEngine->aConsole.propragateMsg("Char Cheat ENABLED!");
                }
                if (renderingEngine->aConsole.consoleString == "power up")
                {
                    CHEAT_InfBoost = true;
                    renderingEngine->aConsole.consoleString == "p-p-p-p-p-POWER UP!";
                }
                if (renderingEngine->aConsole.consoleString == "make it so")
                {
                    entities.cars.at(0)->getActor()->setLinearVelocity(NxVec3(1000,1000,0));
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
                    entities.cars[0]->aCam->resetCamera();
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
    else    //Not in console
    {

    //Keyboard Controls
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if (keyPressed == SDLK_a)
            {
                keyAPressed = true;
            }
            else if (keyPressed == SDLK_d)
            {
                keyDPressed = true;
            }
            else if (keyPressed == SDLK_w)
            {
                keyWPressed = true;
            }
            else if (keyPressed == SDLK_s)
            {
                keySPressed = true;      
            }
            else if (keyPressed == SDLK_INSERT)         //insert logs a waypoint
            {
                logWayPoint(0);
            }
        }

        //keyBoard
        if (KeyboardMouseEvents.type == SDL_KEYUP)
        {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;
            if (keyPressed == SDLK_a)
            {
                keyAPressed = false;
            }
            else if (keyPressed == SDLK_d)
            {
                keyDPressed = false;
            }
            else if (keyPressed == SDLK_w)
            {
                keyWPressed = false;
            }
            else if (keyPressed == SDLK_s)
            {
                keySPressed = false;      
            }
        }
    }


        //Commands runnable in both console and not_in_console mode
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if (keyPressed == SDLK_F1)
            {if (showConsole){showConsole=false;}else{showConsole=true;}}
        }



    return true;
}

void PlayState::handleXboxEvents(int player,XboxController* state)
{
    if (!gameVariables->isFinished(player))
    {
        handleXboxController(player, entities.cars , state, true);
    }
    else
    {
        //Do AI Controller stuff
        handleXboxController(player, entities.cars ,entities.cars.at(player)->aAI->getControl(), false);
    }
    
}

void PlayState::handleXboxController(int player, std::vector<Entity*> cars ,XboxController* state, bool isHuman)
{

    //logReplay(player, state, 0);      Used to log replay!

    //if (state->back)
    if(raceStarted)
    {
        int carCount = cars.size();
        if (player < carCount)
        {
            if((player == 0) && (isHuman))
            {
                if (state->rs && !rbPressed)
                {
                    logWayPoint(0);
                    rbPressed = true;
                    printf("Point logged pressed\n");
                }
                else if (!state->rs)
                    rbPressed = false;  
            }
        

            //UserCamControl  
            Entity* car = cars[player];
        
            car->aCam->setUserCamControl(NxVec3 (state->rightStick.y, 0, state->rightStick.x));

            if(!state->start && !paused)
            {

                NxVec3 a = car->getActor()->getLinearVelocity();
                //printf("x: %f y: %f z: %f \n",a.x,a.y,a.z);
                int rTriggMag = state->rTrigger;
                int lTriggMag = state->lTrigger;    
                static int count = 0;

                car->addTorque(rTriggMag - lTriggMag);        
                car->setSteeringAngle((state->leftStick.magnitude) * -state->leftStick.x / 24000.0f);

		        if(state->x)
			        car->chargeBattery();
		        if(state->y)
			        car->dischargeBattery();
                if(state->b)
                    car->brake(5000);
                else
                    car->brake(0);   

                if(state->a)
                {
                    Entity::PickupType type = car->usePickup();
                    if(type == Entity::MISSILE)
                    {
                        int numCars = gameVariables->numberOfAIs + gameVariables->getNumPlayers();
                        int victimIndex = car->rank - 2;   //offset from current rank to get the person infront of you                 
                        soundEngine->playSound(-1, 8);       //play missile, on channel 4
                        Entity* e = new Entity(20000,
                            physicsEngine->createMissile(car->getActor()),
                            renderingEngine->getModelManger().getModel("Missile.obj")); //Missile will live for 20000 ms.
                        e->rc.push_back(new RenderableComponent(4,32));      //Missile                    
				        e->parent = car;
                        e->initDir = car->getActor()->getGlobalOrientation()*NxVec3(1,0,0);

                        if(victimIndex >= 0) //Fly straight if player is in first place
                        {
                            e->tracking = rankings->at(victimIndex);
                            rankings->at(victimIndex)->tracker = e;
                        }

                        entities.DynamicObjs.push_back(e);

                        if (CHEAT_InfPowUp)
                        {car->givePickup(Entity::MISSILE);}
                    }
                    else if(type == Entity::SHIELD)
                    {
                        soundEngine->playSound(4, 9);       //play missile, on channel 4
                        car->setShield(true);
                    }
                    else if(type == Entity::BARRIER)
                    {
                        soundEngine->playSound(4, 10);       //play missile, on channel 4
                        Entity* e = new Entity(-1,
                            physicsEngine->createBarrier(car->getActor()),
                            renderingEngine->getModelManger().getModel("BarrierDisc.obj")); //Barrier will live forever       
				        e->parent = car;                
                        e->rc.push_back(new RenderableComponent(9,30));      //BarrierDisc
                        int barrierTexture = 83;
                        if (rand() % 10 == 0){barrierTexture = 83 + rand() % 4;}
                        e->rc.push_back(new RenderableComponent(10,barrierTexture));     //BarrierScreen
                        entities.DynamicObjs.push_back(e);

                        if (CHEAT_InfPowUp)
                        {car->givePickup(Entity::BARRIER);}
                    }
                    else if(type == Entity::BOOST)
                    {
                        car->boost();

                        if (CHEAT_InfBoost)
                        {car->givePickup(Entity::BOOST);};
                    }
                }
        
                if(state->dpadUp)
                    car->givePickup(Entity::BARRIER);
                if(state->dpadRight)
                    car->givePickup(Entity::SHIELD);
                if(state->dpadLeft)
                    car->givePickup(Entity::BOOST);
                if(state->dpadDown)
                    car->givePickup(Entity::MISSILE);
                if(state->lb) 
                    car->shuntLeft();
                if(state->rb)
                    car->shuntRight();
                if(state->back)
                {
			        CustomData* cd = (CustomData*)car->getActor()->userData;

                    NxVec3 respawnPt = cd->wp->pos;
                    //NxVec3 ori = cd->wp->ori;
                    //float angle = acos(cd->wp->ori.dot(NxVec3(1,0,0)));

                    car->getActor()->setGlobalPosition(respawnPt);
                    //NxVec3 v(0,1,0);

                    //NxQuat q;
                    //q.fromAngleAxis(angle*(180.0f/3.14f), v);
			        NxMat33 orient(cd->wp->ori);
			        /*
			        NxVec3 temp1 = orient.getColumn(0);
			        NxVec3 temp2 = orient.getColumn(1);
			        NxVec3 temp3 = orient.getColumn(2);
			        printf("%f %f %f\n%f %f %f\n%f %f %f\n\n", temp1[0],temp1[1],temp1[2],temp2[0],temp2[1],temp2[2],temp3[0],temp3[1],temp3[2]);
			        */

                    //orient.fromQuat(q);

                    car->getActor()->setGlobalOrientation(orient);
                    car->getActor()->setLinearVelocity(NxVec3(0,0,0));
                    car->aCam->resetCamera();
			        /*
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
			        */
	            }
            }
            else if (state->start && time.getDeltaTime(pauseTime) > maxPauseTime)
            {
                pauseTime = time.getCurrentTime();
                pause();
            }
        }
    }
}

void PlayState::handleEvents()
{
    handleCollisionEvents();
    handleSoundEvents();
    handleWaypointEvents();
}

void PlayState::handleCollisionEvents()
{
    std::vector<CollisionEvent*>* collisions = eventManager->getCollisionEvents();
    Entity* e1;
    Entity* e2;
    CollisionEvent* collision;

    for(unsigned i=0;i<collisions->size();i++)
    {
        collision = collisions->at(i);
        e1 = collision->entity1;
        e2 = collision->entity2;

        if (collision->action == CollisionEvent::DESTROY_FIRST)
        {
            e1->kill();
            e2->collide(e1);            
        }
        else if (collision->action == CollisionEvent::DESTROY_SECOND)
        {            
            e1->collide(e2);
            e2->kill();
        }
        else if (collision->action == CollisionEvent::DESTROY_BOTH)
        {
            e1->kill();
            e2->kill();
        }
        else if (collision->action == CollisionEvent::DESTROY_NONE)
        {
            e2->collide(e1);
            e1->collide(e2);
        }
    }
    collisions->clear();
}

void PlayState::handleSoundEvents()
{
    std::vector<SoundEvent*>* sounds = eventManager->getSoundEvents();    
    SoundEvent* sound;
    for(unsigned i=0;i<sounds->size();i++)
    {
        sound = sounds->at(i);
        soundEngine->playSound(sound->ch,sound->sIndex);       
    }    
    sounds->clear();
}

void PlayState::handleTriggerEvents()
{
    std::vector<TriggerEvent*>* triggers = eventManager->getTriggerEvents();
    TriggerEvent* trigger;
    for(unsigned i=0;i<triggers->size();i++)
    {
        trigger = triggers->at(i);
        //*********Handle trigger events here***********
    }
    triggers->clear();
}

void PlayState::handleWaypointEvents()
{
    std::vector<WaypointEvent*>* waypoints = eventManager->getWaypointEvents();
    WaypointEvent* waypoint;
    for(unsigned i=0;i<waypoints->size();i++)
    {
        waypoint = waypoints->at(i);
        //********Handle waypoint events here***********
    }
    waypoints->clear();
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
    //NxVec3 ori = car->getActor()->getGlobalOrientation()*NxVec3(1,0,0);
	NxVec3 col0 = car->getActor()->getGlobalOrientation().getColumn(0);
	NxVec3 col1 = car->getActor()->getGlobalOrientation().getColumn(1);
	NxVec3 col2 = car->getActor()->getGlobalOrientation().getColumn(2);

    NxVec3 spd = car->getActor()->getLinearVelocity();
    float spdF = car->getActor()->getLinearVelocity().magnitude();

    float brk0 = car->getDriveWheels()->at(0)->getBrakeTorque();
    float brk1 = car->getDriveWheels()->at(1)->getBrakeTorque();

        std::ofstream out;
        out.open( "replay.txt", std::ios_base::app );
        if( !out )
        {
           printf( "Couldn't open file.\n");
        }
        else
        {
           out << "WAYPOINT " << renderingEngine->FloatToString(loc.x) + " " + renderingEngine->FloatToString(loc.y) + " " + renderingEngine->FloatToString(loc.z);
           //out << " "+renderingEngine->FloatToString(ori.x) + " " + renderingEngine->FloatToString(ori.y) + " " + renderingEngine->FloatToString(ori.z);
		   out << " "+renderingEngine->FloatToString(col0[0]) + " " + renderingEngine->FloatToString(col0[1]) + " " + renderingEngine->FloatToString(col0[2]);
		   out << " "+renderingEngine->FloatToString(col1[0]) + " " + renderingEngine->FloatToString(col1[1]) + " " + renderingEngine->FloatToString(col1[2]);
		   out << " "+renderingEngine->FloatToString(col2[0]) + " " + renderingEngine->FloatToString(col2[1]) + " " + renderingEngine->FloatToString(col2[2]);
           out << " "+renderingEngine->FloatToString(id)+" "+renderingEngine->FloatToString(id+1)+"\n";
           id++;
           //out << "loc: " + renderingEngine->FloatToString(loc.x) + " " + renderingEngine->FloatToString(loc.y) + " " + renderingEngine->FloatToString(loc.z) + char(10) + char(13);
           //out << "ori0: " + renderingEngine->FloatToString(ori.getRow(0).x) + " " + renderingEngine->FloatToString(ori.getRow(0).y) + " " + renderingEngine->FloatToString(ori.getRow(0).z) + char(10) + char(13);
           //out << "ori1: " + renderingEngine->FloatToString(ori.getRow(1).x) + " " + renderingEngine->FloatToString(ori.getRow(1).y) + " " + renderingEngine->FloatToString(ori.getRow(1).z) + char(10) + char(13);
           //out << "ori2: " + renderingEngine->FloatToString(ori.getRow(2).x) + " " + renderingEngine->FloatToString(ori.getRow(2).y) + " " + renderingEngine->FloatToString(ori.getRow(2).z) + char(10) + char(13);
           ////out << "spd: " + renderingEngine->FloatToString(spd.x) + " " + renderingEngine->FloatToString(spd.y) + " " + renderingEngine->FloatToString(spd.z) + char(10) + char(13);
           //out << "spd: " + renderingEngine->FloatToString(spdF) + char(10) + char(13);
           //out << "brk0: " + renderingEngine->FloatToString(brk0) + char(10) + char(13);
           //out << "brk1: " + renderingEngine->FloatToString(brk1) + char(10) + char(13);
        }
        out.close();
}

void PlayState::pause()
{
    paused = !paused; //toggle pause.
}

PlayState* PlayState::getInstance() 
{    
     printf("play state\n");
    static PlayState playState;
    playState.changeState(PLAY);
    return &playState;
}


void PlayState::calculateRankings()
{
    unsigned numCars = rankings->size();
    std::vector<Entity*>* newRankings = new std::vector<Entity*>;
    std::vector<Entity*>* players;

    for(int i=3; i >= 0; i--)
    {
        players = getPlayersOnLap(i);
        sortPlayersByWaypoint(players);
        newRankings->insert(newRankings->end(), players->begin(), players->end());
    }

    rankings->clear();
    rankings->insert(rankings->begin(), newRankings->begin(), newRankings->end());

    for(unsigned i=0;i<rankings->size();i++)
        rankings->at(i)->rank = i+1;
}

std::vector<Entity*>* PlayState::getPlayersOnLap(int lap)
{
    unsigned numCars = rankings->size();
    std::vector<Entity*>* players = new std::vector<Entity*>;
    CustomData* cd;

    for(unsigned i = 0; i < numCars; i++)
    {
        cd = (CustomData*) rankings->at(i)->getActor()->userData;
        if (cd->laps == lap)
            players->push_back(rankings->at(i));
    }

    return players;
}

void PlayState::sortPlayersByWaypoint(std::vector<Entity*>* players)
{
    CustomData* tmpCdi;
    CustomData* tmpCdj;
    Entity* tmpEntity;
    
    unsigned numCars = players->size();
    for(unsigned i = 0; i < numCars; i++)
    {
        tmpCdi = (CustomData*) players->at(i)->getActor()->userData;
        for(unsigned j = i; j < numCars; j++)
        {
            tmpCdj = (CustomData*) players->at(j)->getActor()->userData;
            if(tmpCdi->wp->id < tmpCdj->wp->id) //Handle racers on a different lap
            {
                    tmpEntity = players->at(i);
                    players->at(i) = players->at(j);            
                    players->at(j) = tmpEntity;
            }
            else if(tmpCdi->wp->id == tmpCdj->wp->id) //Handle racers on a different lap
            {
                float iDistanceToNextWp = (players->at(i)->getActor()->getGlobalPosition() - tmpCdi->wp->nextWaypoint->pos).magnitude();
                float jDistanceToNextWp = (players->at(j)->getActor()->getGlobalPosition() - tmpCdj->wp->nextWaypoint->pos).magnitude();
                
                if(iDistanceToNextWp > jDistanceToNextWp)
                {
                    tmpEntity = players->at(i);
                    players->at(i) = players->at(j);            
                    players->at(j) = tmpEntity;
                }
            }
        }
    }
}
