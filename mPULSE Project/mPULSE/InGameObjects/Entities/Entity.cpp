#include "Entity.h"

Entity::Entity()
{
	batteryCharged = false;
	charge = 0.0;
    usingDisplayList = false;
    displayListIndex = -1;

    torque = 0;
    
    minSteering = 0.1f;
    maxSteering = 0.85f;

    maxTorque = 3000;
    minTorque = -3000;
    //Pickup = NULL
}

Entity::Entity(NxActor* a)
{
    actor = a;
}

void Entity::givePickup(Pickup* p)
{
    pickup = p;
}

void Entity::usePickup()
{
    
    if(pickup != NULL)
    {
        pickup->use();//printf();        
    }
    else
        printf("No Pickups Aquired");

    printf("\n");    
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
            torque = static_cast<int>(torque * 0.6f);
        else
            torque = 0;
    }

    if((torque + tmpTorque) < maxTorque && (torque + tmpTorque) > minTorque)
    {
        torque += tmpTorque;
        for (unsigned i = 0; i < driveWheels.size(); ++i)
            driveWheels[i]->setMotorTorque(static_cast<float>(torque));
    }
}

void Entity::brake(int tmpTorque)
{
    for (unsigned i = 0; i < driveWheels.size(); ++i)
        driveWheels[i]->setBrakeTorque(static_cast<float>(tmpTorque));
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

void Entity::setSteeringAngle(float percent)
{
    float maxDeltaAngle = 0;
    float steeringAngle = 0;

    steeringAngle = convertVel(getActor()->getLinearVelocity().magnitude()) * percent;

    for (unsigned i = 0; i < driveWheels.size(); ++i)
        driveWheels[i]->setSteerAngle(steeringAngle);

    //printf("percent: %f angle: %f vel: %f\n",percent,steeringAngle,getActor()->getLinearVelocity().magnitude());
}


void Entity::chargeBattery()
{
	if(!batteryCharged)
	{
		batteryCharged = true;
		NxVec3 lin_vel = actor->getLinearVelocity();
		NxReal speed = lin_vel.magnitude();
		lin_vel.setMagnitude(speed/2.0);
		charge = lin_vel.magnitude();
	
		actor->setLinearVelocity(lin_vel);
	}
}


void Entity::dischargeBattery()
{
	if(batteryCharged)
	{
		batteryCharged = false;
		NxVec3 lin_vel = actor->getLinearVelocity();
		NxReal speed = lin_vel.magnitude();
		lin_vel.setMagnitude(speed + charge);

		actor->setLinearVelocity(lin_vel);
	}
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