#include "Entity.h"

Entity::Entity()
{
    aWheel1 = NULL;
    aWheel2 = NULL;
    aWheel3 = NULL;
	aWheel4 = NULL;
}
/*
void Entity::addComponent(EntityComponent* com)
{
    components.push_back(com);
}
*/

void Entity::setWheel1(NxWheelShape* wheel1)
{
    aWheel1 = wheel1;
}

void Entity::setWheel2(NxWheelShape* wheel2)
{
	aWheel2 = wheel2;
}

void Entity::setWheel3(NxWheelShape* wheel3)
{
	aWheel3 = wheel3;
}

void Entity::setWheel4(NxWheelShape* wheel4)
{
	aWheel4 = wheel4;
}

NxWheelShape* Entity::getWheel1()
{
	return aWheel1;
}

NxWheelShape* Entity::getWheel2()
{
	return aWheel2;
}

NxWheelShape* Entity::getWheel3()
{
	return aWheel3;
}

NxWheelShape* Entity::getWheel4()
{
	return aWheel4;
}

NxActor* Entity::getActor()
{
    return actor;
}

ObjModel* Entity::getModel()
{
    return model;
}

void Entity::setModel(ObjModel* m)
{
    model = m;
}

void Entity::setActor(NxActor* a)
{
    actor = a;
}