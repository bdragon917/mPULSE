#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <NxActor.h>

#include <InGameObjects/Entities/Entity.h>
#include <AI/Waypoint.h>

class Track
{
	struct rc
	{
		int m;
		int t;
	};

	struct additional
	{
		int music;
		std::vector<int> sky;
		int physics;
		std::vector<rc> pairs;
	};

public:   
    Track(std::string trackInfo, Entity* trackEntity);

    void loadTrackInfo(std::string fileName);
	void loadTrackAdditions(std::string filename);
    //void addWaypoint(float xPos, float yPos, float zPos,float xOri, float yOri,float zOri,int tmpId,int next,Waypoint::TYPE type);
    void addWaypoint(Waypoint* wp);  
    std::vector<Waypoint*>* getWaypoints();  
    std::vector<Waypoint*>* getWaypointsOfType(Waypoint::TYPE type);   
    Waypoint* getFirst();
    Waypoint* getWaypoint(int index);
    std::string getName();
    Entity* getEntity();
    NxActor* getActor();     

private:
	additional infoz;

    Waypoint::TYPE stringToType(std::string typeString);
    void finalizeWaypoints();
    std::string removeFilePath(std::string line);
    std::vector<Waypoint*> waypoints;
    std::string trackName;
    //std::vector<waypoint> startWaypoints;
    //std::vector<waypoint> finishWaypoints;    
    //std::vector<waypoint> carSpawnWaypoints;
    //std::vector<waypoint> itemSpawnWaypoints;
    Entity* entity;     //waypointsEntity

    
};

