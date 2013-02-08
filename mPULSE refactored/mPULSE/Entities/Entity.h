#pragma once
#include "EntityComponent.h"
#include <vector>

class Entity
{
public:
    Entity();
    std::vector<EntityComponent*> components;
    
private:
    //std::vector<EntityComponent*> components;
    //Vec force
    
};