#include "Waypoint.h"

Waypoint::Waypoint()
{}

Waypoint::Waypoint(float x, float y, float z)
{pos.x = x; pos.y = y; pos.z=z;}

Waypoint::Waypoint(NxVec3 aVec)
{pos = aVec;}