#include "Entity.h"

Entity::Entity()
{
    usingDisplayList = false;
    displayListIndex = -1;

    torque = 0;
    steeringAngle = 0;
    
    maxSteeringAngle = 0.01;

    maxSteeringLeft = -0.85;
    maxSteeringRight = 0.85;
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
    NxWheelContactData nxwcd;           //memory for contact data
    //driveWheels[0]->getContact(nxwcd);  //get contact data
    if (!(driveWheels[0]->getContact(nxwcd) == NULL))       //get contact data. ==NULL if tires not in contact with anything
    {driveWheels[0]->getActor().addForce(NxVec3(0,-getActor()->getLinearVelocity().magnitude()*1000,0));};      //apply force to hold it to the track
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

void Entity::addSteeringAngle(float percent)
{   
    float maxDeltaAngle = 0;

    if(percent == 0)
    {
        if (0.1 - steeringAngle < 0.1)
            steeringAngle = 0;
        else if(steeringAngle > 0)
            steeringAngle -= 0.1;
        else if(steeringAngle < 0)
            steeringAngle += 0.1;
    }  

    if(getActor()->getLinearVelocity().magnitude() < 30)
    {
        maxDeltaAngle = 0.2;
    }
    else if(getActor()->getLinearVelocity().magnitude() < 60)
    {
        maxDeltaAngle = 0.01;
    }
    else
    {
        maxDeltaAngle = 0.005;
    }

    float deltaAngle = maxDeltaAngle * percent;
    printf("angle: %f\n", deltaAngle);

    if(((steeringAngle+deltaAngle) >= maxSteeringLeft) && ((steeringAngle+deltaAngle) <= maxSteeringRight))
        steeringAngle += deltaAngle;


    //Might be more intuitive for the steering Angle to be set rather than add?
    //This is a test for it
    //steeringAngle = maxDeltaAngle * percent * 2.0f;       //No traction at high speeds for some reason...



    for(int i=0;i<driveWheels.size();i++)
    {
        driveWheels[i]->setSteerAngle(steeringAngle);
    }

  

    //maxSteeringAngle = ((1.0f/(getActor()->getLinearVelocity().magnitude()+0.001)) * 0.01);
    //if(angle == 0)
    //{
    //    if (0.1 - steeringAngle < 0.1)
    //        steeringAngle = 0;
    //    else if(steeringAngle > 0)
    //        steeringAngle -= 0.1;
    //    else if(steeringAngle < 0)
    //        steeringAngle += 0.1;

    //    for(int i=0;i<driveWheels.size();i++)
    //        driveWheels[i]->setSteerAngle(steeringAngle);
    //}    
    //else if(angle >= maxSteeringAngle)
    //    angle = maxSteeringAngle;
    //else if(angle <= maxSteeringAngle*-1)
    //    angle = -maxSteeringAngle;
    //

    //if(((steeringAngle+angle) >= maxSteeringLeft) && ((steeringAngle+angle) <= maxSteeringRight))
    //    steeringAngle += angle;

    //printf("%f\n",angle);

    //for(int i=0;i<driveWheels.size();i++)
    //{
    //    //if(getActor()->getLinearVelocity().magnitude() == 0)
    //        driveWheels[i]->setSteerAngle(steeringAngle);
    //    //else
    //    //   driveWheels[i]->setSteerAngle(steeringAngle*(1.0f/getActor()->getLinearVelocity().magnitude()));
    //}
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