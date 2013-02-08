#pragma once
#include "EntityComponent.h"
#include <vector>

class Entity
{
public:
    Entity();
    std::vector<EntityComponent*> components;

    NxWheelShape* aWheel1;
    NxWheelShape* aWheel2;
    NxWheelShape* aWheel3;
    
private:
    //std::vector<EntityComponent*> components;
    //Vec force
    
};