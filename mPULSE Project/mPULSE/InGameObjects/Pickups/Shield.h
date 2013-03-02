#pragma once
#include <InGameObjects/Pickups/Pickup.h>

class Entity;

class Shield : public Pickup
{

public:
    Shield(void);
    ~Shield(void);
    Entity* use();
};

