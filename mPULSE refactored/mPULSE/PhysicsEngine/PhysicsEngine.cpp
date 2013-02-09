#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	sceneSetup();
}


PhysicsEngine* PhysicsEngine::getInstance()
{
    static PhysicsEngine physics;
    return &physics;
}

void PhysicsEngine::setupPlayScene(vector<Entity*>* cars)
{
    std::vector<Entity*>* tmpCars =  cars;
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

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	//defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	groundPlane = createGroundPlane();
	//box = createBox();

    NxActor* box = createCarChassis();              //create a Chassis
    NxWheelShape* wheel = AddWheelToActor(box, 1.0f,-0.5,1.2);     //Create a wheel, and attach it to the Chassis
	NxWheelShape* wheel2 = AddWheelToActor(box, 1.0f,-0.5,-1.2);
    NxWheelShape* wheel3 = AddWheelToActor(box, -1.0f,-0.5,0.0);
    //NxWheelShape* wheel3 = AddWheelToActor(box, -0.5f,0.05);

    Entity* entityCar1 = new Entity();    
    EntityComponent* ec_car = new EntityComponent();
    ec_car->setActor(box);
    entityCar1->setWheel1(wheel);
	entityCar1->setWheel2(wheel2);
    entityCar1->setWheel3(wheel3);
    //Camera newCamera = Camera(box);
    entityCar1->aCam = new Camera(box);

   // entityCar1.components.push_back( &ec_car );
    entityCar1->addComponent( ec_car );    
    tmpCars->at(0) = entityCar1;    
    tmpCars->at(0)->aWheel1->getActor().addTorque(NxVec3(0,10000000000.0f,0));       //This works! But controls can't get to this for some reason???
	tmpCars->at(0)->aWheel2->getActor().addTorque(NxVec3(0,10000000000.0f,0));
    tmpCars->at(0)->aWheel3->getActor().addTorque(NxVec3(0,10000000000.0f,0));
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


NxActor* PhysicsEngine::createBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;

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
	actor->userData = (void*)size_t(0.5f);

	return actor;
}

NxActor* PhysicsEngine::createStaticBox(float x, float y, float z) 
{
	//Set the box starting height
	NxVec3 position(x, y, z);

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	//boxDesc.localPose.t = position;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body = NULL;                  //Set as static
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);
	actor->userData = (void*)size_t(0.5f);

	return actor;
}

NxActor* PhysicsEngine::createCarChassis() 
{
	//Set the box starting height
	NxVec3 position(0.0, 3.5, 0.0);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;
	
	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxShapes[2];
	boxShapes[0].dimensions.set(2.5f, 0.4f, 1.2f);
	boxShapes[1].dimensions.set(1.f, 0.3f, 1.1f);
	boxShapes[1].localPose.t.set(-0.3f, 0.7f, 0.f);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxShapes[0]);
	actorDesc.shapes.pushBack(&boxShapes[1]);
	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = position;

	NxActor *actor = scene->createActor(actorDesc);

    actor->raiseBodyFlag(NX_BF_FROZEN_ROT_X);
	actor->raiseBodyFlag(NX_BF_FROZEN_ROT_Z);

   
    

	return actor;
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

	NxReal heightModifier = 0.01f;  //??    //(wheelDesc->wheelSuspension + wheelDesc->wheelRadius) / wheelDesc->wheelSuspension;

	wheelShapeDesc.suspension.spring = 1.0f;    //??     //wheelDesc->springRestitution*heightModifier;
	wheelShapeDesc.suspension.damper = 0;  //wheelDesc->springDamping*heightModifier;
	wheelShapeDesc.suspension.targetValue = 0.02f;  //wheelDesc->springBias*heightModifier;

	wheelShapeDesc.radius = 0.25f;  //wheelDesc->wheelRadius;
	wheelShapeDesc.suspensionTravel =  0.1f; //wheelDesc->wheelSuspension; 
	wheelShapeDesc.inverseWheelMass = 0.1;	//not given!? TODO



    NxTireFunctionDesc latff;
    latff.asymptoteSlip = 2.0f;
    latff.asymptoteValue = 0.01f;
    latff.extremumSlip = 1.0f;
    latff.extremumValue = 0.02f;
    latff.stiffnessFactor = 1000000.0f;

    NxTireFunctionDesc lotff;
    lotff.asymptoteSlip = 2.0f;
    lotff.asymptoteValue = 0.01f;
    lotff.extremumSlip = 1.0f;
    lotff.extremumValue = 0.02f;
    lotff.stiffnessFactor = 1000000.0f;

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


NxScene* PhysicsEngine::getScene()
{
	return scene;
}