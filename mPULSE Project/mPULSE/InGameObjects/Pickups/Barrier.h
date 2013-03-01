#pragma once
#include "Pickup.h"
//#include "Entity.h"
#include <stdio.h>

class Entity;

class Barrier : public Pickup
{
public:
    Barrier(void);
    ~Barrier(void);
    Entity* use();
};

