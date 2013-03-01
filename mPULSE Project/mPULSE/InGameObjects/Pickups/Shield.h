#pragma once
#include "Pickup.h"
//#include "Entity.h"
#include <stdio.h>

class Entity;

class Shield : public Pickup
{

public:
    Shield(void);
    ~Shield(void);
    Entity* use();
};

