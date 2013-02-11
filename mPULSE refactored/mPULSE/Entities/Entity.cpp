#include "Entity.h"

Entity::Entity()
{
    torque = 0;
}

void Entity::addDriveWheel(NxWheelShape* wheel)
{
    driveWheels.push_back(wheel);
}

void Entity::addPassiveWheel(NxWheelShape* wheel)
{
    passiveWheels.push_back(wheel);
}

void Entity::addTorque(int tmpTorque)
{
    torque += tmpTorque;
    for(int i=0;i<driveWheels.size();i++)
        driveWheels[i]->setMotorTorque(tmpTorque);
}

void Entity::brake(int tmpTorque)
{
    for(int i=0;i<driveWheels.size();i++)
        driveWheels[i]->setBrakeTorque(tmpTorque);
}

void Entity::addSteeringAngle(float angle)
{
    steeringAngle += angle;
    for(int i=0;i<driveWheels.size();i++)
        driveWheels[i]->setSteerAngle(driveWheels[i]->getSteerAngle() + angle);
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