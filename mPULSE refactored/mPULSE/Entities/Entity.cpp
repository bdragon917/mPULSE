#include "Entity.h"

Entity::Entity()
{
    torque = 0;
    steeringAngle = 0;
    maxSteeringLeft = -0.35;
    maxSteeringRight = 0.35;
    maxTorque = 2000;
    minTorque = -2000;
    model = NULL;
}

Entity::Entity(NxActor* a)
{
    actor = a;
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
    if(tmpTorque == 0)
    {
        if (torque > 200)
            torque = torque*.6;
        else 
            torque = 0;
    }

    if((torque + tmpTorque) < maxTorque && (torque + tmpTorque) > minTorque)
    {
        torque += tmpTorque;
        for(int i=0;i<driveWheels.size();i++)
            driveWheels[i]->setMotorTorque(torque);
    }
}

void Entity::brake(int tmpTorque)
{
    for(int i=0;i<driveWheels.size();i++)
        driveWheels[i]->setBrakeTorque(tmpTorque);
}

void Entity::addSteeringAngle(float angle)
{
    if(angle == 0)
    {
        if (0.1 - steeringAngle < 0.1)
            steeringAngle = 0;
        else if(steeringAngle > 0)
            steeringAngle -= 0.1;
        else if(steeringAngle < 0)
            steeringAngle += 0.1;

        for(int i=0;i<driveWheels.size();i++)
            driveWheels[i]->setSteerAngle(steeringAngle);
    }

    else if(((steeringAngle+angle) >= maxSteeringLeft) && ((steeringAngle+angle) <= maxSteeringRight))
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