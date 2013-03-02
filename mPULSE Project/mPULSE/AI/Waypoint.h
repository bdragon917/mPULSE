#pragma once
#include <NxPhysics.h>

class Waypoint
{
public:
    Waypoint();
    Waypoint(float x, float y, float z,int tmpId,int next);
    Waypoint(NxVec3 aVec,int tmpId,int next);

    NxVec3 pos;
    float remSpd;   //recommended Speed
    float brakeDur; //If brake, how long to hold it for
    int id;
    int nextId;
    Waypoint* nextWaypoint;
    typedef enum TYPE {START, FINISH, WAYPOINT, CAR_SPAWN, ITEM_SPAWN, INVALID_TYPE};
    TYPE type;
};

