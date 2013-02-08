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
	box = createCar();
    //Entity aCar;
    //EntityComponent aCC;
    //aCC.setActor( createCar() );
    //aCar.components.push_back ( &aCC );
    //cars.push_back( &aCar );
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
	box = createCar();
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


NxActor* PhysicsEngine::createCar() 
{
	NxBodyDesc bodyDesc;
	NxBoxShapeDesc boxShapes[2];

	boxShapes[0].dimensions.set(2.5f, 0.4f, 1.2f);
	boxShapes[1].dimensions.set(1.f, 0.3f, 1.1f);
	boxShapes[1].localPose.t.set(-0.3f, 0.7f, 0.f);

	NxActorDesc actorDesc;

	actorDesc.body = &bodyDesc;
    bodyDesc.mass = 5;
    bodyDesc.sleepEnergyThreshold = 0.05f;

	actorDesc.shapes.pushBack(&boxShapes[0]);
	actorDesc.shapes.pushBack(&boxShapes[1]);

	//Set the car starting height
	NxVec3 position(0.0, 3.5, 0.0);

	//Add single shape actor to the scene

	actorDesc.globalPose.t = position;
	NxActor *actor = scene->createActor(actorDesc);
	/*
    //Binding wheels
    NxWheelShapeDesc wShapeDesc;
    //wShapeDesc.localPose.t = location?
    wShapeDesc.suspension.spring = 2.0f;//(suspension * wheelRadius / suspension)
    wShapeDesc.suspension.damper = 0.0f;
    wShapeDesc.suspension.targetValue = 1.0f;

    wShapeDesc.radius = 1.0f;
    wShapeDesc.suspensionTravel = 1.0f; // 
	wShapeDesc.inverseWheelMass = 0.1f;
	//actor->userData = (void*)size_t(0.5f);

    actor->createShape (wShapeDesc);
	*/
	return actor;
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