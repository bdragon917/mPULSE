#pragma once
#include "Pickup.h"
//#include "Entity.h"
#include <stdio.h>

class Entity;

class MissileLauncher : public Pickup
{
public:
    MissileLauncher(void);
    ~MissileLauncher(void);
    Entity* use();
};

