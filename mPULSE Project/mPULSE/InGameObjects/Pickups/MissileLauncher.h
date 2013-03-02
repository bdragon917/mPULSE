#pragma once
#include <InGameObjects/Pickups/Pickup.h>

class Entity;

class MissileLauncher : public Pickup
{
public:
    MissileLauncher(void);
    ~MissileLauncher(void);
    Entity* use();
};

