#include "InGameObjects\CustomData.h"

CustomData::CustomData(ObjTypes tmpType, int tmpPickup, int lapCount, Waypoint* waypoint)
{
    type = tmpType;
    pickupType = tmpPickup;
    laps = lapCount;
    wp = waypoint;
    entity = NULL;
}

CustomData::CustomData(Waypoint* waypoint)
{
    type = NONE;
    pickupType = -1;
    laps = -1;
    wp = waypoint;
    entity = NULL;
}
