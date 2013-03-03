#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "NxActor.h"

#include <InGameObjects/Entities/Entity.h>
#include <AI/Waypoint.h>

class Track
{
public:   
    Track(std::string trackInfo, Entity* trackEntity);
    Track();

    void loadTrackInfo(std::string fileName);
    void addWaypoint(float xPos, float yPos, float zPos,float xOri, float yOri,float zOri,int tmpId,int next,Waypoint::TYPE type);
    void addWaypoint(Waypoint* wp);  
    std::vector<Waypoint*>* getWaypoints();    
    std::vector<Waypoint*>* getWaypointsOfType(Waypoint::TYPE type);   
    void Track::finalizeWaypoints();
    Waypoint* getFirst();
    Waypoint* getWaypoint(int index);
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

