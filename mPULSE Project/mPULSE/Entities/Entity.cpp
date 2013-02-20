#include "Entity.h"

Entity::Entity()
{
    usingDisplayList = false;
    displayListIndex = -1;

    torque = 0;
    
    minSteering = 0.1;
    maxSteering = 0.85;

    maxTorque = 3000;
    minTorque = -3000;
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
    ///* Can use this to keep better contact with the ground
    NxWheelContactData nxwcd; //memory for contact data
    //driveWheels[0]->getContact(nxwcd); //get contact data
    //if (!(driveWheels[0]->getContact(nxwcd) == NULL)) //get contact data. ==NULL if tires not in contact with anything
    //{driveWheels[0]->getActor().addForce(NxVec3(0,-getActor()->getLinearVelocity().magnitude()*1000,0));}; //apply force to hold it to the track
   // */

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

float Entity::convertVel(float vel)
{
    float deltaSteer = 0.0;
    float sensitivity = 7.0;

    if(vel == 0)
        deltaSteer = minSteering;
    else
        deltaSteer = sensitivity / vel;

    if(deltaSteer < minSteering)
        deltaSteer = minSteering;
    else if(deltaSteer > maxSteering)
        deltaSteer = maxSteering;

    return deltaSteer;
}

void Entity::addSteeringAngle(float percent)
{
    float maxDeltaAngle = 0;
    float steeringAngle = 0;

    steeringAngle = convertVel(getActor()->getLinearVelocity().magnitude()) * percent;

    for(int i=0;i<driveWheels.size();i++)
        driveWheels[i]->setSteerAngle(steeringAngle);

    //printf("percent: %f angle: %f vel: %f\n",percent,steeringAngle,getActor()->getLinearVelocity().magnitude());
}


NxActor* Entity::getActor()
{
    return actor;
}
std::vector<NxWheelShape*> Entity::getDriveWheels()
{return driveWheels;}

std::vector<NxWheelShape*> Entity::getPassiveWheels()
{return passiveWheels;}



void Entity::setUsingDisplayList(bool status)
{
    usingDisplayList = status;
}
void Entity::setDisplayListIndex(int index)
{
    setUsingDisplayList(true);
    displayListIndex = index;
}
int Entity::getDisplayListIndex()
{
    return displayListIndex;
}
bool Entity::getUsingDisplayList()
{
    return usingDisplayList;
}

void Entity::setActor(NxActor* a)
{
    actor = a;
}