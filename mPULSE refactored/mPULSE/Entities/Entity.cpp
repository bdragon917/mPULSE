#include "Entity.h"

Entity::Entity()
{
    torque = 0;
    steeringAngle = 0;
    maxSteeringLeft = -0.5;
    maxSteeringRight = 0.5;
    maxTorque = 2000;
    minTorque = -2000;
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
    if((torque + tmpTorque) < maxTorque && (torque + tmpTorque) > minTorque)
    {
        torque += tmpTorque;
        for(int i=0;i<driveWheels.size();i++)
            driveWheels[i]->setMotorTorque(torque);
    }
}

void Entity::addSteeringAngle(float angle)
{
    if(((steeringAngle+angle) >= maxSteeringLeft) && ((steeringAngle+angle) <= maxSteeringRight))
    {
        steeringAngle += angle;
        for(int i=0;i<driveWheels.size();i++)
            driveWheels[i]->setSteerAngle(steeringAngle);
    }
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