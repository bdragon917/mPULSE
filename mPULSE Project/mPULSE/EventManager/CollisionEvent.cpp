#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, Action a)
{
    entity1 = e1;
    entity2 = e2;
    action = a;
}

CollisionEvent::~CollisionEvent(void)
{
}
