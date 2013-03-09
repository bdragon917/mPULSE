#pragma once
#include "../AI/Waypoint.h"


class CustomData
{
    public:
        Waypoint* wp;
        enum  ObjTypes { CAR, TRACK, OBSTACLE, STATIC, WAYPOINT};
        ObjTypes type;
        int pickupType;
        int laps;
};