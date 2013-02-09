#include "Entity.h"

Entity::Entity()
{
    aWheel1 = NULL;
    aWheel2 = NULL;
    aWheel3 = NULL;
}

void Entity::addComponent(EntityComponent* com)
{
    components.push_back(com);
}


void Entity::setWheel1(NxWheelShape* wheel1)
{
    aWheel1 = wheel1;
}

void Entity::setWheel2(NxWheelShape* wheel2)
{
	aWheel2 = wheel2;
}