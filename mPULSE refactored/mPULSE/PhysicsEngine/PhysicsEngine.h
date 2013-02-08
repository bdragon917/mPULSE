#pragma once

#define NOMINMAX
#include "Physics.h"
#include <NxPhysics.h>
#include "PhysXLoader.h"
#include <NxPhysicsSDK.h>
#include <NxActor.h>
#include "../Entities/Entity.h"

#include <vector>
//#include "NxWheelDesc.h"

using std::vector;

class PhysicsEngine
{
private:
	NxPhysicsSDK* physicsSDK;
	NxScene* scene;

	NxActor* groundPlane;
	NxActor* box;

	NxReal deltaTime;

    NxMaterial* wsm;

    NxWheelShape* AddWheelToActor(NxActor* actor);

public:
    PhysicsEngine();
	static PhysicsEngine* getInstance();
	void sceneSetup();
    void step();//float dt, Physics* physData);
	void releaseNx();
	void resetNx();
    void setupPlayScene(vector<Entity*>* cars);      //Use this to initalize the physicScene for playState

	NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength);
	NxVec3 ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength);
	NxActor* createGroundPlane();
	NxActor* createBox();
    NxActor* createCarChassis();
//    NxWheelShape* AddWheelToActor(NxActor* actor, NxWheelDesc* wheelDesc);
    void resetBox();

	NxScene* getScene();
};

