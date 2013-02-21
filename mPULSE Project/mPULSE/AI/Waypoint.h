#pragma once
#include <NxPhysics.h>

class Waypoint
{
public:
    NxVec3 pos;
    float remSpd;   //recommended Speed
    float brakeDur; //If brake, how long to hold it for
};

