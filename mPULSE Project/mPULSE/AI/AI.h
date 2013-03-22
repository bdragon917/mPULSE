#pragma once
#define NOMINMAX
#include <InGameObjects/Entities/Entity.h>
#include <Input/XboxController.h>
#include <NxPhysics.h>
#include <NxActor.h>
#include <AI/Waypoint.h>
#include <math.h>
#include <InGameObjects/CustomData.h>

//#include <InGameObjects/Track.h>
//#include <InGameObjects/Entities/Entity.h>
#include <vector>
#include <AI\AIPersonality.h>
//#include <InGameObjects\Entities\Entities.h>

class Entity;



class AI
{
public:
    AI();

    AIPersonality myPersonality;

    XboxController* getControl();
    void update(std::vector<Entity*> players, std::vector<Entity*> AIs);

    void setWaypoint(Waypoint* aW);
    void setActor(NxActor* aA);
    
    void setPersonality(int type);

    NxActor* getActor();

    Entity* anEntity;

    NxVec3 myTargetVector;   //For debug
    NxVec3 myOrientation;
private:



    Waypoint* targetWaypoint;
    NxActor* myActor;
    NxVec3 myLocation;
    
    NxVec3 addBoydFlocking(NxVec3 curTargetVector, std::vector<Entity*> AIs, std::vector<Entity*> Players);
    NxVec3 attackPlayerInRange(NxVec3 myTarget, std::vector<Entity*> Players);
    void AI::applySpeedBoost(std::vector<Entity*> AIs);


    XboxController* xController;
};

