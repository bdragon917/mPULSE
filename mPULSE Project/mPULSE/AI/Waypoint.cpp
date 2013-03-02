#include "Waypoint.h"

Waypoint::Waypoint()
{
    pos.x = 0; pos.y = 0; pos.z=0;
    id = 0;
    nextId = 0;
}

Waypoint::Waypoint(float x, float y, float z,int tmpId,int tmpNext)
{
    pos.x = x; pos.y = y; pos.z=z;
    id = tmpId;
    nextId = tmpNext;
}

Waypoint::Waypoint(NxVec3 aVec,int tmpId,int tmpNext)
{
    pos = aVec;
    id = tmpId;
    nextId = tmpNext;
}