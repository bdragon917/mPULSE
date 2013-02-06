#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	deltaTime = 1.0/60.0;
	physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	physicsSDK->setParameter(NX_SKIN_WIDTH, 0.01);

	sceneSetup();
}


PhysicsEngine* PhysicsEngine::getInstance()
{
    static PhysicsEngine physics;
    return &physics;
}


void PhysicsEngine::sceneSetup()
{
	NxSceneDesc sceneDesc;
	sceneDesc.simType = NX_SIMULATION_SW;
	NxVec3 defaultGravity(0,-9.8,0);
	sceneDesc.gravity = defaultGravity;
	scene = physicsSDK->createScene(sceneDesc);

	//Create the default material
	NxMaterial* defaultMaterial = scene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);

	groundPlane = createGroundPlane();
	box = createBox();
}


void PhysicsEngine::simulate(float dt, Physics* physData)
{

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
	NxReal boxStartHeight = 3.5;

	//Add single shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	//The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(0.5,0.5,0.5);
	boxDesc.localPose.t = NxVec3(0,0,0);
	actorDesc.shapes.pushBack(&boxDesc);

	actorDesc.body = &bodyDesc;
	actorDesc.density = 10.0f;
	actorDesc.globalPose.t = NxVec3(0,boxStartHeight,0);
	assert(actorDesc.isValid());
	NxActor *actor = scene->createActor(actorDesc);
	assert(actor);

	return actor;
}


void PhysicsEngine::startPhysics()
{
	scene->simulate(deltaTime);
	scene->flushStream();
}


NxScene* PhysicsEngine::getScene()
{
	return scene;
}