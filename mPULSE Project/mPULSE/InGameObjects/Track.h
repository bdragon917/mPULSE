#pragma once
#include "Entities\Entity.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "NxActor.h"

#include "../AI/Waypoint.h"

class Track
{
public:   
    //typedef enum TYPE {START, FINISH, WAYPOINT, CAR_SPAWN, ITEM_SPAWN, INVALID_TYPE};

    //typedef struct
    //{        
    //    float x;
   //     float y;
   //     float z;
    //    TYPE type;
    //} Waypoint;    

    Track(std::string trackInfo, Entity* trackEntity);
    Track();

    void loadTrackInfo(std::string fileName);
    void addWaypoint(float x,float y,float z,Waypoint::TYPE type);
    void addWaypoint(Waypoint* wp);
    std::vector<Waypoint*>* getWaypoints();    
    std::vector<Waypoint*>* getWaypointsOfType(Waypoint::TYPE type);   
    Entity* getEntity();
    NxActor* getActor();     

private:
    Waypoint::TYPE stringToType(std::string typeString);

    std::vector<Waypoint*> waypoints;
    //std::vector<waypoint> startWaypoints;
    //std::vector<waypoint> finishWaypoints;    
    //std::vector<waypoint> carSpawnWaypoints;
    //std::vector<waypoint> itemSpawnWaypoints;
    Entity* entity;     //waypointsEntity

    
};

