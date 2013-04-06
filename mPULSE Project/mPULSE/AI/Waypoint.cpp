#include <AI/Waypoint.h>

Waypoint::Waypoint()
{
    pos.x = 0; pos.y = 0; pos.z=0;
    id = 0;
    nextId = 0;
}

Waypoint::Waypoint(std::vector<std::string>* info)
{
    pos.x   = NxReal(atof(info->at(1).data()));
    pos.y   = NxReal(atof(info->at(2).data()));
    pos.z   = NxReal(atof(info->at(3).data()));

    id      = atoi(info->at(4).data());
    nextId  = atoi(info->at(5) .data());
}

/*
Waypoint::Waypoint(float x, float y, float z,float xOri, float yOri, float zOri,int tmpId,int tmpNext)
{
    pos.x = x; pos.y = y; pos.z=z;
    id = tmpId;
    nextId = tmpNext;
}

Waypoint::Waypoint(NxVec3 position,NxVec3 orientation,int tmpId,int tmpNext)
{
    pos = position;
    ori = ori;
    id = tmpId;
    nextId = tmpNext;
}
*/