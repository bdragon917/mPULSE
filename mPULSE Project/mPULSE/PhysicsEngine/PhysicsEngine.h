#pragma once

#define NOMINMAX
#include <NxPhysics.h>
#include "PhysXLoader.h"
#include <NxPhysicsSDK.h>
#include <NxActor.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/TriggerCallback.h>
#include <AI/Waypoint.h>
#include <InGameObjects/CustomData.h>
#include "stream.h"
#include <cstdlib>
#include <NxCooking.h>
#include <vector>
#include <InGameObjects/ContactReport.h>

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
    ContactReport contactReport;
    NxMaterial* wsm;

	TriggerCallback myTriggerCallback;

    NxActorGroup carGroup;
    NxActorGroup pickupsGroup;

    NxWheelShape* AddWheelToActor(NxActor* actor, float x,float y, float z);

    //Creating spawnpoints
    NxReal startX;
    NxReal startZ;
    NxReal offset;

public:

    //enum  ObjTypes { CAR, TRACK, OBSTACLE, STATIC };

    //typedef struct
    //{
    //    ObjTypes type;
    //}   customUserData;
    
       

    PhysicsEngine();

    NxVec3 PhysicsEngine::getNewSpawnPoint();
    void generateSpawnPoints(Waypoint* wp);
    void updateSpawnPoints(Waypoint* wp,vector<Entity*>* cars,vector<Entity*>* AIcars);
	static PhysicsEngine* getInstance();
	void sceneSetup();
    void step(float deltaTime);//float dt, Physics* physData);
	void releaseNx();
	void resetNx();
    void setupPlayScene(vector<Entity*>* cars);      //Use this to initalize the physicScene for playState
    void setupCars(vector<Entity*>* cars);
    void destroy(NxActor* actor);
	NxActor* createGroundPlane();
	NxActor* createBox(float x, float y, float z);
    void createBoxes(float x, float y, float z, int num, float radius, std::vector<Entity*>* Boxes);
    NxActor* createStaticBox(float x, float y, float z);
    NxActor* createTriMesh(float x, float y, float z, ObjModel aModel);
    NxActor* createCarChassis();
    NxActor* createBarrier(NxActor* car);
    NxActor* createMissile(NxActor* car);
	void createWaypoints(std::vector<Waypoint*>* waypoints);

    void resetBox();  
    void resetBoxHigh();

	NxScene* getScene();


};

