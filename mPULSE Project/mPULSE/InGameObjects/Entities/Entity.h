#pragma once

#include <vector>
#include "NxPhysics.h"

#include <GameStates/Camera.h>
#include <ModelLoader/ObjModel.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <AI/AI.h>
#include <InGameObjects/Pickups/Pickup.h>
#include "Util\Clock.h"
#include "InGameObjects\CustomData.h"

//Forward declarations
class AI;
class CustomData;

class Entity
{
public:

   typedef enum {
        MISSILE,
        SHIELD,
        BARRIER,
        NONE
    } PickupType;

    Entity(int tmpTimeToLive = -1, NxActor* a = NULL, ObjModel* tmpModel = NULL);
    NxVec3 carStartPos;
    //std::vector<EntityComponent*> components;
    Camera* aCam;
    //void addComponent(EntityComponent* com);
    void addDriveWheel(NxWheelShape* wheel);
    void addPassiveWheel(NxWheelShape* wheel);
    void addSteerWheel(NxWheelShape* wheel);
    void addTorque(int tmpTorque);
	void brake(int tmpTorque);
    void setSteeringAngle(float angle);
	void chargeBattery();
	void dischargeBattery();
    void givePickup(PickupType type);
    PickupType usePickup();

    //void setModel(ObjModel* m);
    void setActor(NxActor* a);
    void setModel(ObjModel* m);
    void setDisplayListIndex(int index);
    void setUsingDisplayList(bool status);
    int getDisplayListIndex();
    int getTorque();
    int getSteering();
    bool getUsingDisplayList();
	NxActor* getActor();
    ObjModel* getModel();
    float convertVel(float vel);
    std::vector<NxWheelShape*>* getDriveWheels();
    std::vector<NxWheelShape*>* getPassiveWheels();    
    std::vector<NxWheelShape*>* getSteerWheels();
    //Drawing stuff
    //list of renderableElements [model index, texture index]
    std::vector<RenderableComponent*> rc;
    //NxVec3 location for rendering
    //int rotation mode
    //rotation data    

	NxSweepQueryHit* linearSweep(float dt);

    AI* aAI;
    void setTimeToLive(int tmpTime);
    void setCustomData(CustomData* cd);
    void kill();
    void collide(Entity* e);

    void shuntRight();
    void shuntLeft();
    void deshunt();

    float tiltAngle;

    int getTimeToLive();

    bool getShield();
    void setShield(bool active);
    void update();

    void reset();
    bool isAlive();
    bool hasShield();
    bool isBatteryCharged();
    bool isShunting();

	void highSpeedCash();
	float raceWinnings();
	void missleCash();

	bool getSweepCollision();
	void setSweepCollision(bool b);
	NxVec3 getImpactPoint();
	void setImpactPoint(NxVec3 point);
	NxVec3 getImpactNormal();
	void setImpactNormal(NxVec3 normal);
	NxVec3 getOldVelocity();
	void setOldVelocity(NxVec3 oldVelocity);
	NxReal getDotResult();
	void setDotResult(NxReal result);
    int rank;
	Entity* parent;
    	unsigned obs;
    std::string rankingName;

private:

	bool batteryCharged;
    bool usingDisplayList;
    bool alive;
    bool shunting;
    bool steering;
    bool shield;
	bool sweepCollision;

    int displayListIndex;
    int torque;
    int maxTorque;
    int minTorque;
    int timeToLive;
    int timeCreated;
    int shieldActivatedTime;     
    int health;

	unsigned highSpeedObsTime;
	
    
    float maxSteeringAngle;
    float minSteering;
    float maxSteering;
	float charge;

    unsigned shuntStartTime;
    unsigned maxShuntTime;
    unsigned shuntReloadTime;
    unsigned shieldTimeout;   
    NxReal shuntPower;

	NxVec3 impactPoint;
	NxVec3 impactNormal;
	NxVec3 oldVelocity;
	NxReal dotResult;

    Clock clock;
    PickupType pickup;
    NxActor* actor;
    ObjModel* model;
    std::vector<NxWheelShape*> driveWheels;
    std::vector<NxWheelShape*> steerWheels;
    std::vector<NxWheelShape*> passiveWheels;
};