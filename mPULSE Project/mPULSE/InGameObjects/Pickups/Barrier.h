#pragma once
#include <InGameObjects/Pickups/Pickup.h>

class Entity;

class Barrier : public Pickup
{
public:
    Barrier(void);
    ~Barrier(void);
    Entity* use();
};

