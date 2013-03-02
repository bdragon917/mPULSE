#include "Waypoint.h"

Waypoint::Waypoint()
{
    pos.x = 0; pos.y = 0; pos.z=0;
    id = 0;
    nextExpected = 0;
}

Waypoint::Waypoint(float x, float y, float z,int tmpId,int next)
{
    pos.x = x; pos.y = y; pos.z=z;
    id = tmpId;
    nextExpected = next;
}

Waypoint::Waypoint(NxVec3 aVec,int tmpId,int next)
{
    pos = aVec;
    id = tmpId;
    nextExpected = next;
}