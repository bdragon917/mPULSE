#pragma once

#define NOMINMAX

#include <vector>
#include <InGameObjects/Entities/Entity.h>

class Entities
{
public:
        std::vector<Entity*> cars;
        std::vector<Entity*> AIcars;
        std::vector<Entity*> Obstacles;
        std::vector<Entity*> StaticObjs;
        std::vector<Entity*> DynamicObjs;
        std::vector<Entity*> Track;
};
