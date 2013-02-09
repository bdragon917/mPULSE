#pragma once
#include "EntityComponent.h"
#include <vector>
#include "..\GameStates\Camera.h"

class Entity
{
public:
    Entity();
    std::vector<EntityComponent*> components;

    NxWheelShape* aWheel1;
    NxWheelShape* aWheel2;
    NxWheelShape* aWheel3;

    //Camera aCam;
    
    void addComponent(EntityComponent* com);
    void setWheel1(NxWheelShape* wheel1);
	void setWheel2(NxWheelShape* wheel2);
    void setWheel3(NxWheelShape* wheel3);

private:
    //std::vector<EntityComponent*> components;
    //Vec force
    
};