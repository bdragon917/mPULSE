#include "Waypoint.h"

Waypoint::Waypoint()
{
    pos.x = 0; pos.y = 0; pos.z=0;
    id = 0;
    next = 0;
}

Waypoint::Waypoint(float x, float y, float z,int tmpId,int tmpNext)
{
    pos.x = x; pos.y = y; pos.z=z;
    id = tmpId;
    next = tmpNext;
}

Waypoint::Waypoint(NxVec3 aVec,int tmpId,int tmpNext)
{
    pos = aVec;
    id = tmpId;
    next = tmpNext;
}