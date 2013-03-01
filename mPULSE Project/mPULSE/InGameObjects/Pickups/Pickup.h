#pragma once
#include "../Entities/Entity.h"

class Entity;

class Pickup
{
public:
    Pickup();
    ~Pickup();

    virtual Entity* use()=0;
};

