#pragma once

#define NOMINMAX
#include "Physics.h"
#include <NxPhysics.h>
#include "PhysXLoader.h"
#include <NxPhysicsSDK.h>
#include <NxActor.h>
#include "../InGameObjects/Entities/Entity.h"
#include "../InGameObjects/TriggerCallback.h"

#include "stream.h"
#include <cstdlib>

#include <NxCooking.h>

#include <vector>

//#include <iostream>
//#include "NxWheelDesc.h"

using std::vector;

class PhysicsEngine
{
private:
	NxPhysicsSDK* physicsSDK;
	NxScene* scene;

	NxActor* groundPlane;
	NxActor* box;

    NxMaterial* wsm;

	TriggerCallback myTriggerCallback;



    NxWheelShape* AddWheelToActor(NxActor* actor, float x,float y, float z);

public:

    enum  ObjTypes { CAR, TRACK, OBSTACLE, STATIC };

    typedef struct
    {
        ObjTypes type;
    }   customUserData;
    
       

    PhysicsEngine();
	static PhysicsEngine* getInstance();
	void sceneSetup();
    void step(float deltaTime);//float dt, Physics* physData);
	void releaseNx();
	void resetNx();
    void setupPlayScene(vector<Entity*>* cars);      //Use this to initalize the physicScene for playState
    void setupCars(vector<Entity*>* cars);

	NxActor* createGroundPlane();
	NxActor* createBox(float x, float y, float z);
    void createBoxes(float x, float y, float z, int num, float radius, std::vector<Entity*>* Boxes);
    NxActor* createStaticBox(float x, float y, float z);
    NxActor* createTriMesh(float x, float y, float z, ObjModel aModel);
    NxActor* createCarChassis();
    NxActor* createBarrier(NxVec3 pos,NxVec3 dir);
    NxActor* createMissile(NxVec3 pos,NxVec3 dir);

    void resetBox();
    void resetBoxHigh();

	NxScene* getScene();

};

