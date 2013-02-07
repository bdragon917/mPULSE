#pragma once

#define NOMINMAX
#include "Physics.h"
#include <NxPhysics.h>
#include "PhysXLoader.h"
#include <NxPhysicsSDK.h>
#include <NxActor.h>

class PhysicsEngine
{
private:
	NxPhysicsSDK* physicsSDK;
	NxScene* scene;

	NxActor* groundPlane;
	NxActor* box;

	NxReal deltaTime;

public:
    PhysicsEngine();
	static PhysicsEngine* getInstance();
	void sceneSetup();
    void step();//float dt, Physics* physData);

	NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength);
	NxVec3 ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength);
	NxActor* createGroundPlane();
	NxActor* createBox();

	NxScene* getScene();
};

