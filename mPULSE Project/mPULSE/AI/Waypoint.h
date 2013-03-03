#pragma once
#include <NxPhysics.h>

class Waypoint
{
public:
    Waypoint();
    Waypoint(float xPos, float yPos, float zPos,float xOri, float yOri, float zOri,int tmpId,int next);
    Waypoint(NxVec3 position,NxVec3 orientation,int tmpId,int next);

    NxVec3 pos;
    NxVec3 ori;
    float remSpd;   //recommended Speed
    float brakeDur; //If brake, how long to hold it for
    int id;
    int nextId;
    Waypoint* nextWaypoint;
    typedef enum TYPE {START, FINISH, WAYPOINT, CAR_SPAWN, PICKUP_SPAWN, INVALID_TYPE};
    TYPE type;
};

