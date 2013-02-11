#pragma once

#define NOMINMAX
#include "Physics.h"
#include <NxPhysics.h>
#include "PhysXLoader.h"
#include <NxPhysicsSDK.h>
#include <NxActor.h>
#include "../Entities/Entity.h"

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
    void losing();
	//NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength);
	//NxVec3 ApplyForceToBox(const NxVec3& forceDir, const NxReal forceStrength);
	NxActor* createGroundPlane();
	NxActor* createBox(float x, float y, float z);
    void createBoxes(float x, float y, float z, int num, float radius);
    NxActor* createStaticBox(float x, float y, float z);
    NxActor* createTriMesh(float x, float y, float z, ObjModel aModel);
    NxActor* createCarChassis();
//    NxWheelShape* AddWheelToActor(NxActor* actor, NxWheelDesc* wheelDesc);
    void resetBox();
    void resetBoxHigh();

	NxScene* getScene();
	void accel();
	void rev();
	void steer(int);

    	NxWheelShape* w1;
	NxWheelShape* w2;
	NxWheelShape* w3;
	NxWheelShape* w4;

};

