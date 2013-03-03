#pragma once
#define NOMINMAX
#include <Input/XboxController.h>
#include <NxPhysics.h>
#include <NxActor.h>
#include <AI/Waypoint.h>
#include <math.h>
#include <InGameObjects/CustomData.h>

//#include <InGameObjects/Track.h>
//#include <InGameObjects/Entities/Entity.h>

class AI
{
public:
    AI(void);
    ~AI(void);

    XboxController* getControl();
    void update();

    void setWaypoint(Waypoint* aW);
    void setActor(NxActor* aA);
    NxActor* getActor();

    NxVec3 myTargetVector;   //For debug
    NxVec3 myOrientation;
private:

    Waypoint* targetWaypoint;
    NxActor* myActor;
    NxVec3 myLocation;
    

    XboxController* xController;
};

