#pragma once
#include "EntityComponent.h"
#include <vector>

class Entity
{
public:
    Entity();
    
private:
    std::vector<EntityComponent*> components;
    //Vec force
    
};