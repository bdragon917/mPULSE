#pragma once
#include "Waypoint.h"
#include <InGameObjects/Entities/Entity.h>
#include <vector>
#include <iostream>
#include <fstream>


class Waypoints
{
public:
    Waypoints(void);
    ~Waypoints(void);

    Waypoint getCurrentWaypoint(int player);
    Waypoint getNextWaypoint(int player);
    std::vector<Entity> getNearbyPlayers(int player);
    std::vector<Entity> getNearbyCars(int player);

    void loadWaypoints(std::string filename);


private:
    std::vector<Entity*> cars;
    std::vector<Waypoint> waypointList;
};

