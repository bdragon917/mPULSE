#pragma once
#include <NxPhysics.h>

class Waypoint
{
public:
    Waypoint();
    Waypoint(float x, float y, float z);
    Waypoint(NxVec3 aVec);

    NxVec3 pos;
    float remSpd;   //recommended Speed
    float brakeDur; //If brake, how long to hold it for

    typedef enum TYPE {START, FINISH, WAYPOINT, CAR_SPAWN, ITEM_SPAWN, INVALID_TYPE};
    TYPE type;
};

