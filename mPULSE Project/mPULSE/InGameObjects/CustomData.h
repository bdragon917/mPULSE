#pragma once
#include "AI\Waypoint.h"
#include "InGameObjects\Entities\Entity.h"

class Entity;

class CustomData
{
public:
    typedef enum { 
        CAR, 
        TRACK,
        OBSTACLE,
        STATIC,
        WAYPOINT,
        MESH,
        NONE
    } ObjTypes;

    CustomData(ObjTypes tmpType=NONE, int tmpPickup=-1, int lapCount=-1, Waypoint* waypoint=NULL);    
    CustomData(Waypoint* waypoint);  
    ObjTypes type;
    int pickupType;
    int laps;
    Waypoint* wp;
    Entity* entity;
};