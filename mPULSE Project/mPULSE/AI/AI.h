#pragma once
#define NOMINMAX
#include "../Input/XboxController.h"
#include <NxPhysics.h>
#include <NxActor.h>
#include "../AI/Waypoint.h"
//#include "../InGameObjects/Track.h"
//#include "../Entities/Entity.h"

class AI
{
public:
    AI(void);
    ~AI(void);

    XboxController* getControl();
    void update();

    void setWaypoint(Waypoint* aW);
    void setActor(NxActor* aA);


    NxVec3 myTargetVector;   //For debug
private:

    Waypoint* targetWaypoint;
    NxActor* myActor;
    NxVec3 myLocation;
    NxVec3 myOrientation;

    XboxController* xController;
};

