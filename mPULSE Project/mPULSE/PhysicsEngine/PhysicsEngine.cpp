#include <PhysicsEngine/PhysicsEngine.h>

std::vector<NxVec3*> spawnPoints;
int curSP;
int maxSP;


PhysicsEngine::PhysicsEngine()
{
	sceneSetup();

}


void PhysicsEngine::updateSpawnPoints(Waypoint* wp,vector<Entity*>* cars,vector<Entity*>* AIcars)
{
    startX = wp->pos.x + 9;
    startZ = wp->pos.z - 3;
    NxReal startY = 5;
    offset = -6;
    curSP = 0;
    maxSP = 8;

    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset; 
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset; 
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;   startX = 7; startZ+=offset;
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset; 
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;
    spawnPoints.push_back(new NxVec3 (startX,startY,startZ));      startX+=offset;            

    vector<Entity*> allCars = *cars;
    vector<Entity*> allAiCars = *AIcars;

    for(unsigned i=0;i<allCars.size();i++)
    {
        if(curSP>maxSP){curSP=0;}
        cars->at(i)->getActor()->setGlobalPosition(*spawnPoints[curSP++]);
        cars->at(i)->aCam->resetCamera();
    }

    for(unsigned i=0;i<allAiCars.size();i++)
    {
        if(curSP>maxSP){curSP=0;}
        allAiCars.at(i)->getActor()->setGlobalPosition(*spawnPoints[curSP++]);
        allAiCars.at(i)->aCam->resetCamera();
    }
}
NxVec3 PhysicsEngine::getNewSpawnPoint()
{

    NxVec3 retValue = NxVec3(startX,3,startZ);

    //if (startX == 9)
    {startX+=offset;}
    //else
    //{
    //    startX-=offset;
    //    startX = 7;
   // }
    
    return retValue;
}


PhysicsEngine* PhysicsEngine::getInstance()
{
    static PhysicsEngine physics;
    return &physics;
}

void PhysicsEngine::setupPlayScene(vector<Entity*>* cars)
{
    //std::vector<Entity*>* tmpCars =  cars;
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);

    physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTIVE_VERTICES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
    physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);


	NxSceneDesc sceneDesc;
	sceneDesc.simType = NX_SIMULATION_SW;
	NxVec3 defaultGravity(0,-9.8f*(10.0f),0);
	sceneDesc.gravity = defaultGravity;
	scene = physicsSDK->createScene(sceneDesc);

	//Set up so that trigger objects in the scene will sent an event to TriggerReport
	scene->setUserTriggerReport(&myTriggerCallback);
    scene->setUserContactReport(&contactReport); 
    //FIXME: ContactReport
    scene->setActorGroupPairFlags(carGroup,pickupsGroup,CustomData::CAR | CustomData::OBSTACLE);

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	//defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	//groundPlane = createGroundPlane();
	//box = createBox();

    setupCars(cars);

 }

void PhysicsEngine::setupCars(vector<Entity*>* cars)
{
    for (unsigned pxCars = 0; pxCars < cars->size(); ++pxCars)
    {

        NxActor* box = createCarChassis();              //create a Chassis
        NxWheelShape* wheel =  AddWheelToActor(box, 1.0f, 0, 1.2f) ;     //Create a wheel, and attach it to the Chassis
	    NxWheelShape* wheel2 = AddWheelToActor(box, 1.0f, 0, -1.2f);
        NxWheelShape* wheel3 = AddWheelToActor(box, -1.0f, 0, 1.2f);
	    NxWheelShape* wheel4 = AddWheelToActor(box, -1.0f, 0, -1.2f);
        
        //FIXME: ContactReport
        box->setContactReportFlags(NX_NOTIFY_ON_TOUCH);

        //NxWheelShape* wheel3 = AddWheelToActor(box, -0.5f,0.05);
        //Entity* entityCar1 = new Entity();
        Entity* entityCar1 = cars->at(pxCars);

        //EntityComponent* ec_car = new EntityComponent();
        //ec_car->setActor(box);
        //RenderableComponent* rc = new RenderableComponent(1,3);
        //entityCar1->rc.push_back(rc);
        entityCar1->addDriveWheel(wheel);
        entityCar1->addSteerWheel(wheel);

	    entityCar1->addDriveWheel(wheel2);
        entityCar1->addSteerWheel(wheel2);

		entityCar1->addDriveWheel(wheel3);
        entityCar1->addPassiveWheel(wheel3);

		entityCar1->addDriveWheel(wheel4);
	    entityCar1->addPassiveWheel(wheel4);

        //Camera newCamera = Camera(box);
        entityCar1->aCam = new Camera(box);

       // entityCar1.components.push_back( &ec_car );
        //entityCar1->addComponent( ec_car );    
	    entityCar1->setActor(box);
        //cars->at(pxCars) = entityCar1;

        if (&(cars->at(pxCars)->carStartPos) == NULL)
        {printf("carStartPos is nul\n");}

	    box->setSleepEnergyThreshold(0);
        
    }
}

void PhysicsEngine::sceneSetup()
{
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);    
	NxSceneDesc sceneDesc;
    sceneDesc.simType = NX_SIMULATION_SW;
    
	NxVec3 defaultGravity(0,-9.8f*(10.0f),0);
	sceneDesc.gravity = defaultGravity;
	scene = physicsSDK->createScene(sceneDesc);
    //scene->setTiming(NxReal(0.016f),NX_TIMESTEP_FIXED); //TODO: Use this?

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	//defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	groundPlane = createGroundPlane();
	box = createBox(0,0,0);
}


void PhysicsEngine::step(float deltaTime)
{
	scene->simulate(deltaTime);
	scene->flushStream();
	scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
    //scene->fetchResults(NX_ALL_FINISHED, true); //TODO: Use this instead?
}


void PhysicsEngine::releaseNx() 
{
	if(scene)
	{
		while(!scene->fetchResults(NX_RIGID_BODY_FINISHED, false));
		physicsSDK->releaseScene(*scene);
	}
	if(physicsSDK) physicsSDK->release();
}


void PhysicsEngine::resetNx()
{
	releaseNx();
	sceneSetup();
}

//Needs deltaTime from gameClock in the Game class
//NxVec3 PhysicsEngine::ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength)
//{
//	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
//	actor->addForce(forceVec);
//	return forceVec;
//}

//Needs deltaTime from gameClock in the Game class
//NxVec3 PhysicsEngine::ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength)
//{
//	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
//	box->addForce(forceVec);
//	return forceVec;
//}


NxActor* PhysicsEngine::createGroundPlane()
{
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	return scene->createActor(actorDesc);
}

NxActor* PhysicsEngine::createBarrier(NxActor* car ) 
{
    float spdMag = car->getLinearVelocity().magnitude();
    float spdOffset = (1.0f / ((spdMag * 0.01f) + 1));
    float offset = -5.0f;
    if (spdOffset > 0.55f)
        offset *= spdOffset;
    else
        offset *= 0.55f;
                                    
     NxVec3 initPos(1.0f,0,0); 
     NxVec3 dir = car->getGlobalOrientation()*initPos;
     NxVec3 pos = car->getGlobalPose().t + (dir*offset); 

	//Set the box starting height
	NxVec3 position(pos.x, pos.y, pos.z);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;
    bodyDesc.flags = NX_BF_FROZEN_POS;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.25f,1.5f,3.3f);
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 0.1f;
    actorDesc.globalPose = car->getGlobalPose();
	actorDesc.globalPose.t = pos;
    
	NxActor *actor = scene->createActor(actorDesc);

    CustomData* cd = new CustomData(CustomData::OBSTACLE,2);
    actor->userData = (void*)cd;   
    
	return actor;
}

NxActor* PhysicsEngine::createMissile(NxActor* car) 
{
    float offset = 5.0f;                               
    NxVec3 initPos(1,0,0); 
    NxVec3 dir = car->getGlobalOrientation()*initPos;
    NxVec3 pos = car->getGlobalPose().t + (dir*offset);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;
    bodyDesc.flags = NX_BF_DISABLE_GRAVITY | NX_BF_FROZEN_ROT;
    
	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
    actorDesc.globalPose = car->getGlobalPose();
	actorDesc.globalPose.t = pos;
    
	NxActor *actor = scene->createActor(actorDesc);
    actor->setContactReportFlags(NX_NOTIFY_ON_START_TOUCH);

    CustomData* cd = new CustomData(CustomData::OBSTACLE,0);
    actor->userData = (void*)cd;      
    
    actor->addLocalForce(NxVec3(100000,0,0) + car->getLinearVelocity());
    
	return actor;
}


void PhysicsEngine::createWaypoints(std::vector<Waypoint*>* wps)
{
	std::vector<Waypoint*> waypoints = *wps;
	for(unsigned i = 0; i<waypoints.size();i++)
	{
        if(waypoints[i]->type == Waypoint::WAYPOINT)
        {
		    NxVec3 position(waypoints[i]->pos);
			//float angle = acos(waypoints[i]->ori.dot(NxVec3(1,0,0)));

			//NxQuat q;
            //q.fromAngleAxis(angle*(180.0f/3.14f), NxVec3(0,1,0));
			NxMat33 orient(waypoints[i]->ori);
            //orient.fromQuat(q);

		    //The actor has one shape, a box, 1m on a side
		    NxBoxShapeDesc boxDesc;
		    boxDesc.dimensions.set(1.0,100.0,100.0);
		    boxDesc.shapeFlags |= NX_TRIGGER_ENABLE;

		    NxActorDesc actorDesc;
		    actorDesc.shapes.pushBack(&boxDesc);
		    actorDesc.globalPose.t = position;
    
		    NxActor *actor = scene->createActor(actorDesc);	
            CustomData* cd = new CustomData(CustomData::WAYPOINT,-1,-1,waypoints[i]);

		    actor->userData = cd; 
			actor->setGlobalOrientation(orient);
        }
        else if(waypoints[i]->type == Waypoint::PICKUP_SPAWN)
        {
		    NxVec3 position(waypoints[i]->pos);

		    //The actor has one shape, a box, 1m on a side
		    NxSphereShapeDesc sphereDesc;
		    sphereDesc.radius = (NxReal)4.0f;
		    sphereDesc.shapeFlags |= NX_TRIGGER_ENABLE;

		    NxActorDesc actorDesc;
		    actorDesc.shapes.pushBack(&sphereDesc);
		    actorDesc.globalPose.t = position;
    
		    NxActor *actor = scene->createActor(actorDesc);		
            CustomData* cd = new CustomData(CustomData::WAYPOINT,waypoints[i]->id,-1,waypoints[i]);

		    actor->userData = cd; 
        }
	}
    
}

void PhysicsEngine::createBoxes(float x, float y, float z, int num, float radius, std::vector<Entity*>* Boxes) 
{
	for (int i=0; i < num; i++)
    {
        float rndx = ((rand() % 100) / 100) * radius;
        float rndz = ((rand() % 100) / 100) * radius;
        Entity* aEntity = new Entity(-1,createBox(x + rndx, y, z + rndz));
        //aEntity->rc.push_back(&(RenderableComponent(0,6)));
        RenderableComponent* rc = new RenderableComponent(21,61 + rand() % 4);        //asteroids , texture = 61 - 64
        aEntity->rc.push_back(rc);
        
        Boxes->push_back(aEntity);
    }
}

NxActor* PhysicsEngine::createBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.1f;
    bodyDesc.linearDamping = 0.5f;
    bodyDesc.flags = NX_BF_DISABLE_GRAVITY;

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
    CustomData* cd = new CustomData(CustomData::OBSTACLE);
    
    actor->userData = (void*)cd;  

	return actor;
}

NxActor* PhysicsEngine::createStaticBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	boxDesc.shapeFlags |= NX_TRIGGER_ENABLE;
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = NULL;                  //Set as static
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
	//actor->userData = (void*)size_t(0.5f);
    CustomData* cd = new CustomData(CustomData::STATIC);
    actor->userData = (void*)cd;
	return actor;
}


/**
This Method doesn't work
**/
NxActor* PhysicsEngine::createTriMesh(float x, float y, float z, ObjModel aModel) 
{
	NxVec3 position(x, y, z);

    NxVec3* gVerts;
    NxVec3* gNormals;
    NxU32* gFaces;

    //aModel.getVerticies()->size();
    gVerts = new NxVec3 [aModel.getVerticies()->size()];
    for (unsigned v = 0; v < aModel.getVerticies()->size(); ++v)
    {
        gVerts[v] = ( NxVec3(aModel.getVerticies()->at(v).x, aModel.getVerticies()->at(v).y, aModel.getVerticies()->at(v).z) );
    }


   // aModel.getVerticies()->size();
    gFaces = new NxU32[(aModel.getFaces()->size()*3)+3];
    //for (int f = 0; f < aModel.getFaces()->size(); f++)
    //{
    //    gFaces[f]
    //}


    for (unsigned v = 0; v < aModel.getFaces()->size(); ++v)
    {
        gFaces[v*3] = ( NxU32(aModel.getFaces()->at(v).at(0).vertIndex) );
        gFaces[(v*3)+1] = ( NxU32(aModel.getFaces()->at(v).at(1).vertIndex) );
        gFaces[(v*3)+2] = ( NxU32(aModel.getFaces()->at(v).at(2).vertIndex) );
    }

    //aModel.getVertexNormals()->size();
    gNormals = new NxVec3[aModel.getVertexNormals()->size()];

    for (unsigned n = 0; n < aModel.getVertexNormals()->size(); ++n)
    {
        gNormals[n] = ( NxVec3(aModel.getVertexNormals()->at(n).x, aModel.getVertexNormals()->at(n).y, aModel.getVertexNormals()->at(n).z) );
    }

    printf("PHYSIC_MESH: Ver:%i, Tri:%i\n",aModel.getVerticies()->size(), aModel.getFaces()->size());

	// Build physical model
	NxTriangleMeshDesc triMeshDesc;
	triMeshDesc.numVertices					= aModel.getVerticies()->size();
	triMeshDesc.numTriangles				= aModel.getFaces()->size();
	triMeshDesc.pointStrideBytes			= sizeof(NxVec3);
	triMeshDesc.triangleStrideBytes			= 3*sizeof(NxU32);
	triMeshDesc.points						= gVerts;
	triMeshDesc.triangles					= gFaces;							
	triMeshDesc.flags						= 0;//NX_MF_HARDWARE_MESH;//0;


	//add the mesh material data:
	//triMeshDesc.materialIndexStride			= sizeof(NxMaterialIndex);
	//triMeshDesc.materialIndices				= gTerrainMaterials;

	//triMeshDesc.heightFieldVerticalAxis		= NX_Y;
	//triMeshDesc.heightFieldVerticalExtent	= -1000.0f;

	NxTriangleMeshShapeDesc triMeshShapeDesc;

    NxInitCooking();

     MemoryWriteBuffer buf;
        NxCookingParams params;  
        params.targetPlatform = PLATFORM_PC;  
        params.skinWidth = 0.1f;  
        params.hintCollisionSpeed = false;  
        NxSetCookingParams(params);  
     bool status = NxCookTriangleMesh(triMeshDesc, buf); 

  	MemoryReadBuffer readBuffer(buf.data);


  	triMeshShapeDesc.meshData = physicsSDK->createTriangleMesh(readBuffer);
    //triMeshShapeDesc.meshFlags = NX_MF_FLIPNORMALS;        //seems to help??
	//
	// Please note about the created Triangle Mesh, user needs to release it when no one uses it to save memory. It can be detected
	// by API "meshData->getReferenceCount() == 0". And, the release API is "gPhysicsSDK->releaseTriangleMesh(*meshData);"
	//
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&triMeshShapeDesc);

    actorDesc.body = NULL;                  //Set as static
	actorDesc.density = 1000.0f;

    actorDesc.globalPose.t = position;
	NxActor *actor = scene->createActor(actorDesc);

    CustomData* cd = new CustomData(CustomData::MESH);    
	actor->userData = (void*)cd;


     //actor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC,true);

	NxCloseCooking();
    return actor;

    //actor->setSleepEnergyThreshold(0);          //Testing
    //return scene->createActor(actorDesc);
}


NxActor* PhysicsEngine::createCarChassis() 
{
	//Set the box starting height
	NxVec3 position(0.0, 53.5, 0.0);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	//bodyDesc.angularDamping	= 0.5f;
	bodyDesc.angularDamping	= 30.0f;
	bodyDesc.linearDamping = 0.05f;


	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxShapes[2];
	
    //boxShapes[0].dimensions.set(2.2f, 0.8f, 1.2f);
	//boxShapes[1].dimensions.set(1.f, 0.3f, 1.1f);
    boxShapes[0].dimensions.set(2.2f, 0.7f, 1.3f);          //This might make it harder to fall trhough stage????
    //boxShapes[0].dimensions.set(1.7f, 0.7f, 1.3f);          //Tighter bounds, but....
	boxShapes[0].localPose.t.set(0.2f, 0.7f, 0.0f);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxShapes[0]);
	//actorDesc.shapes.pushBack(&boxShapes[1]);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;


    float d = 90.0f;      //Turn by 90 degrees

    NxVec3 v(0,1,0);
    NxReal ang = 90;

    NxQuat q;
    q.fromAngleAxis(ang, v);
    NxMat33 orient;
    orient.fromQuat(q);

    //This is done in the play state??
    //CustomData* cd = new CustomData(CustomData::CAR);    
	//actorDesc.userData = cd;   

	NxActor *actor = scene->createActor(actorDesc);
    actor->setCMassOffsetLocalPosition(NxVec3(0, -1.0, 0));
    //actor->setCMassOffsetLocalPosition(NxVec3(0, 0, 0));
    //actor->setCMassOffsetLocalPosition(NxVec3(0.25f, -4.0, 0));   //True Front Weel Drive =)

    actor->setGlobalOrientation(orient);

	return actor;
}

void PhysicsEngine::destroy(NxActor* actor)
{
    scene->releaseActor(*actor);
}

NxWheelShape* PhysicsEngine::AddWheelToActor(NxActor* actor, float x,float y, float z)
{
	NxWheelShapeDesc wheelShapeDesc;

	// Create a shared car wheel material to be used by all wheels
	if (!wsm)
	{
		NxMaterialDesc m;
		m.flags |= NX_MF_DISABLE_FRICTION;
		wsm = scene->createMaterial(m);
	}
	wheelShapeDesc.materialIndex = wsm->getMaterialIndex();


	wheelShapeDesc.localPose.t = NxVec3(x, y, z);//wheelDesc->position;

	NxQuat q;
	q.fromAngleAxis(90, NxVec3(0,1,0));
	wheelShapeDesc.localPose.M.fromQuat(q);


    NxReal wheelSuspension = 2.0f;
    NxReal WheelRadius = 0.5f;
    NxReal heightModifier = wheelSuspension + WheelRadius / wheelSuspension;
	//NxReal heightModifier = 2.0f;  //??    //(wheelDesc->wheelSuspension + wheelDesc->wheelRadius) / wheelDesc->wheelSuspension;

	wheelShapeDesc.suspension.spring = 7000.0f * heightModifier;    //??     //wheelDesc->springRestitution*heightModifier;
	wheelShapeDesc.suspension.damper = 100.0f * heightModifier;  //wheelDesc->springDamping*heightModifier;
	wheelShapeDesc.suspension.targetValue = 0.001f * heightModifier;  //wheelDesc->springBias*heightModifier;

	wheelShapeDesc.radius = 0.5f;  //wheelDesc->wheelRadius;
	wheelShapeDesc.suspensionTravel =  0.5f; //wheelDesc->wheelSuspension; 
	wheelShapeDesc.inverseWheelMass = 0.1f;	//not given!? TODO


    //Sideways ??
    NxTireFunctionDesc latff;
    latff.asymptoteSlip = 2.0f;
    latff.asymptoteValue = 0.01f;
    latff.extremumSlip = 1.0f;
    latff.extremumValue = 0.05f;
    //latff.stiffnessFactor = 1000000.0f;
    latff.stiffnessFactor = 750000.0f;

    //Along the tire??
    NxTireFunctionDesc lotff;
    lotff.asymptoteSlip = 2.0f;
    lotff.asymptoteValue = 0.01f;
    lotff.extremumSlip = 1.0f;
    lotff.extremumValue = 0.02f;
    lotff.stiffnessFactor = 1250000.0f;

    wheelShapeDesc.lateralTireForceFunction = latff;	//TODO
	wheelShapeDesc.longitudalTireForceFunction = lotff;	//TODO

    NxWheelShape* wheelShape;    
	wheelShape = static_cast<NxWheelShape *>(actor->createShape(wheelShapeDesc));     

    return wheelShape;
}

void PhysicsEngine::resetBox()
{
	box->setGlobalPosition(NxVec3(0,3.5,0));
	scene->flushCaches();
}

void PhysicsEngine::resetBoxHigh()
{
	box->setGlobalPosition(NxVec3(0,35.0f,0));
	scene->flushCaches();
}


NxScene* PhysicsEngine::getScene()
{
	return scene;
}
