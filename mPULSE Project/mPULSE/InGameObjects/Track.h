#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <NxActor.h>

#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <GameStates\GameVariables.h>
#include <AI/Waypoint.h>

class Track
{
	//struct rc
	//{
	//	int m;
	//	int t;
	//};

	struct additional
	{
		int music;
		std::vector<int> sky;
		int physics;
		std::vector<RenderableComponent*> pairs;
	};

public:   
    Track(std::string trackInfo, Entity* trackEntity);
    Track(std::string trackInfo);   //remember to set Entity afterwards?? this uses the new file format

    void setEntity(Entity* trackEntity);

    void loadTrackInfo(std::string fileName);
    void Track::loadTrackInfo2(std::string filename);
	void loadTrackAdditions(std::string filename);
    void Track::parseHead(std::vector<std::string>* newData);
    //void addWaypoint(float xPos, float yPos, float zPos,float xOri, float yOri,float zOri,int tmpId,int next,Waypoint::TYPE type);
    void addWaypoint(Waypoint* wp);  
    std::vector<std::string>* split(std::string line, char delimiter);
    std::vector<Waypoint*>* getWaypoints();  
    std::vector<Waypoint*>* getWaypointsOfType(Waypoint::TYPE type);   
    Waypoint* getFirst();
    Waypoint* getWaypoint(int index);
    std::string getName();
    Entity* getEntity();
    NxActor* getActor();   

    additional infoz;

private:
	

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

