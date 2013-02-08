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

void PhysicsEngine::setupPlayScene(vector<Entity*> cars)
{
	deltaTime = 1.0f/60.0f;
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);

    physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTIVE_VERTICES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
    physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
    physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);

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
	box = createBox();

    NxActor* car1 = createCarChassis();

    


   // NxWheelShapeDesc* wheel1 = createCarWheel(car1);
    Entity entityCar1;
    EntityComponent ec_car;
    ec_car.setActor(car1);



    // Steering wheel           //Currently this code doesn't work, when the controller tries to use this, there is null values which crashes the system when read....
    NxWheelDesc wheelDesc1;
   // wheelDesc1.wheelAxis.set(0,0,1);
    //wheelDesc1.downAxis.set(0,-1,0);
    wheelDesc1.wheelApproximation = 10;
    wheelDesc1.wheelRadius = 0.5;
    wheelDesc1.wheelWidth = 0.1;
    wheelDesc1.wheelSuspension = 0.5;
    wheelDesc1.springRestitution = 7000;
    wheelDesc1.springDamping = 0;
    wheelDesc1.springBias = 0;
    wheelDesc1.maxBrakeForce = 1;
    wheelDesc1.frictionToFront = 0.1;
    wheelDesc1.frictionToSide = 0.99;
    wheelDesc1.position = NxVec3(0,1.5f,0);
    wheelDesc1.wheelFlags = NX_WF_USE_WHEELSHAPE | NX_WF_BUILD_LOWER_HALF | NX_WF_ACCELERATED | NX_WF_AFFECTED_BY_HANDBRAKE | NX_WF_STEERABLE_INPUT;

    entityCar1.aWheel1 = AddWheelToActor(car1, &wheelDesc1);

    //left wheel
    NxWheelDesc wheelDesc2;
   // wheelDesc2.wheelAxis.set(0,0,1);
    //wheelDesc2.downAxis.set(0,-1,0);
    wheelDesc2.wheelApproximation = 10;
    wheelDesc2.wheelRadius = 0.5;
    wheelDesc2.wheelWidth = 0.1;
    wheelDesc2.wheelSuspension = 0.5;
    wheelDesc2.springRestitution = 7000;
    wheelDesc2.springDamping = 0;
    wheelDesc2.springBias = 0;
    wheelDesc2.maxBrakeForce = 1;
    wheelDesc2.frictionToFront = 0.1;
    wheelDesc2.frictionToSide = 0.99;
    wheelDesc2.position = NxVec3(1.5,0.5,0);
    wheelDesc2.wheelFlags = NX_WF_USE_WHEELSHAPE | NX_WF_BUILD_LOWER_HALF | NX_WF_ACCELERATED | NX_WF_AFFECTED_BY_HANDBRAKE | NX_WF_STEERABLE_INPUT;

    entityCar1.aWheel2 = AddWheelToActor(car1, &wheelDesc2);



        // Right wheel
    NxWheelDesc wheelDesc3;
    //wheelDesc3.wheelAxis.set(0,0,1);
   // wheelDesc3.downAxis.set(0,-1,0);
    wheelDesc3.wheelApproximation = 10;
    wheelDesc3.wheelRadius = 0.5;
    wheelDesc3.wheelWidth = 0.1;
    wheelDesc3.wheelSuspension = 0.5;
    wheelDesc3.springRestitution = 7000;
    wheelDesc3.springDamping = 0;
    wheelDesc3.springBias = 0;
    wheelDesc3.maxBrakeForce = 1;
    wheelDesc3.frictionToFront = 0.1;
    wheelDesc3.frictionToSide = 0.99;
    wheelDesc3.position = NxVec3(-1.5,0.5,0);
    wheelDesc3.wheelFlags = NX_WF_USE_WHEELSHAPE | NX_WF_BUILD_LOWER_HALF | NX_WF_ACCELERATED | NX_WF_AFFECTED_BY_HANDBRAKE | NX_WF_STEERABLE_INPUT;

    entityCar1.aWheel3 = AddWheelToActor(car1, &wheelDesc3);




    //entityCar1.aWheel1 = //createCarWheel(NxActor* Chassis);   //AddWheelToCar

   // //EntityComponent ec_wheel;
  //  //ec_wheel.setActor(wheel1);


    entityCar1.components.push_back( &ec_car );
   // //entityCar1.components.push_back( &ec_wheel );
    

   // entityCar1.aWheel = wheel1;
   // //cars.push_back( &entityCar1 );
    
    
    
    //Entity aCar;
    //EntityComponent aCC;
    //aCC.setActor( createCar() );
    //aCar.components.push_back ( &aCC );
    cars.push_back( &entityCar1 );
}

void PhysicsEngine::sceneSetup()
{
	deltaTime = 1.0f/60.0f;
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
	box = createBox();
}


void PhysicsEngine::step()//float dt, Physics* physData)
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


NxVec3 PhysicsEngine::ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength)
{
	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
	actor->addForce(forceVec);
	return forceVec;
}


NxVec3 PhysicsEngine::ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength)
{
	NxVec3 forceVec = forceStrength*forceDir*deltaTime;
	box->addForce(forceVec);
	return forceVec;
}


NxActor* PhysicsEngine::createGroundPlane()
{
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	return scene->createActor(actorDesc);
}


NxActor* PhysicsEngine::createBox() 
{
	//Set the box starting height
	NxVec3 position(0.0, 3.5, 0.0);

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


NxActor* PhysicsEngine::createCarChassis() 
{
	//Set the box starting height
	NxVec3 position(0.0, 3.5, 0.0);

	//Add single shape actor to the scene
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;

    //actorDesc.body = STUFF!
	
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


	return actor;
}

NxWheelShape* PhysicsEngine::AddWheelToActor(NxActor* actor, NxWheelDesc* wheelDesc)
{
   NxWheelShapeDesc wheelShapeDesc;

    // Create a shared car wheel material to be used by all wheels
    static NxMaterial* wsm = 0;
    if (!wsm)
    {
        NxMaterialDesc m;
        m.flags |= NX_MF_DISABLE_FRICTION;
        wsm = scene->createMaterial(m);
    }
    wheelShapeDesc.materialIndex = wsm->getMaterialIndex();

    wheelShapeDesc.localPose.t = wheelDesc->position;
    NxQuat q;
    q.fromAngleAxis(90, NxVec3(0,1,0));
    wheelShapeDesc.localPose.M.fromQuat(q);

    NxReal heightModifier = (wheelDesc->wheelSuspension + wheelDesc->wheelRadius) / wheelDesc->wheelSuspension;

    wheelShapeDesc.suspension.spring = wheelDesc->springRestitution*heightModifier;
    wheelShapeDesc.suspension.damper = wheelDesc->springDamping*heightModifier;
    wheelShapeDesc.suspension.targetValue = wheelDesc->springBias*heightModifier;

    wheelShapeDesc.radius = wheelDesc->wheelRadius;
    wheelShapeDesc.suspensionTravel = wheelDesc->wheelSuspension; 
    wheelShapeDesc.inverseWheelMass = 0.1;	//not given!? TODO

    //wheelShapeDesc.longitudalTireForceFunction = wheelDesc->longitudalTireForceFunction;
   // wheelShapeDesc.lateralTireForceFunction = wheelDesc->lateralTireForceFunction;

    NxWheelShape* wheelShape = NULL;
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