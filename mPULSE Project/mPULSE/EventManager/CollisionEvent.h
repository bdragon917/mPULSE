#pragma once
#include "InGameObjects\Entities\Entity.h"

class CollisionEvent
{

public:
    enum Action {DESTROY_BOTH, DESTROY_FIRST, DESTROY_SECOND, DESTROY_NONE};
    CollisionEvent(Entity* e1, Entity* e2, Action a);
    ~CollisionEvent(void);

    Entity* entity1;
    Entity* entity2;
    Action action;

private:
};

