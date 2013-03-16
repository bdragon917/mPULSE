#include <InGameObjects/Entities/Entity.h>

Entity::Entity(int tmpTimeToLive, NxActor* a, ObjModel* tmpModel)
{
    alive = true;
	batteryCharged = false;
    usingDisplayList = false;
    steering = true;
    shunting = false;

	charge = 0.0f;
    displayListIndex = -1;
    actor = a;
    model = tmpModel;

    torque = 0;
    
    minSteering = 0.1f;
    maxSteering = 0.85f;
    maxTorque = 3000;
    minTorque = -3000;
    shield = 0;
    pickup = NONE;

    shuntStartTime = 0;
    shieldActivatedTime = 0;
    shieldTimeout = 10000;
    maxShuntTime = 200;
    shuntPower = 50;
    shuntReloadTime = 600;

    timeToLive = tmpTimeToLive;
    timeCreated = clock.getCurrentTime();

    if(actor != NULL)
    {
        CustomData* cd = (CustomData*) actor->userData;
        if(cd != NULL)
            cd->entity = this;
    }
}

void Entity::update()
{
    if (clock.getCurrentTime() - shieldActivatedTime > shieldTimeout)
        shield = false;
}

void Entity::setTimeToLive(int tmpTime)
{
    timeToLive = tmpTime;
} 

int Entity::getTimeToLive()
{
    return timeToLive;
} 

void Entity::reset()
{

}

void Entity::kill()
{
    alive = false;
    timeToLive = 0;
}

bool Entity::isAlive()
{
    if(alive)
    {
        if(timeToLive==-1)
            alive = true;
    
        if((int)clock.getCurrentTime() - timeCreated >= timeToLive)
            alive = false;
        else
            alive = true;
    }

    return alive;
}

void Entity::givePickup(Entity::PickupType p)
{
    pickup = p;

    CustomData* cd = (CustomData*) actor->userData;
    cd->pickupType = p;
}

Entity::PickupType Entity::usePickup()
{
    CustomData* cd = (CustomData*) actor->userData;
    int type = cd->pickupType;    
    cd->pickupType = -1;

    if(type == 0)
        return MISSILE;
    else if(type == 1)
        return SHIELD;
    else if(type == 2)
        return BARRIER; 
    else
        return NONE;
}

void Entity::shuntRight()
{
    NxWheelContactData nxwcd; 
    driveWheels[0]->getContact(nxwcd); //get contact data

    //Check if already shunting or if off the ground
    if(!shunting && (driveWheels[0]->getContact(nxwcd) != NULL) && (clock.getCurrentTime() - shuntStartTime > shuntReloadTime))
    {
        shuntStartTime = clock.getCurrentTime();
        shunting=true;
        steering = false;

        NxReal angle = 0;
        NxVec3 newDir(0,0,0);
        NxVec3 shuntValue = actor->getGlobalOrientation()*NxVec3(0,0,shuntPower);
        NxVec3 carDir;

        if(actor->getLinearVelocity().magnitude() < 1)
            carDir = actor->getGlobalOrientation()*NxVec3(1,0,0);
        else
            carDir = actor->getLinearVelocity();

        newDir.add(carDir,shuntValue);
        angle = -acos(newDir.dot(carDir) / (newDir.magnitude()*carDir.magnitude()));
        
        unsigned size = getDriveWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getDriveWheels()->at(i)->setSteerAngle(angle);

        size = getSteerWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getSteerWheels()->at(i)->setSteerAngle(angle);

        size = getPassiveWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getPassiveWheels()->at(i)->setSteerAngle(angle);

        actor->setLinearVelocity(newDir);
    }    
}

void Entity::shuntLeft()
{
    NxWheelContactData nxwcd; 
    driveWheels[0]->getContact(nxwcd); //get contact data

    //Check if already shunting or if off the ground
    if(!shunting && (driveWheels[0]->getContact(nxwcd) != NULL) && (clock.getCurrentTime() - shuntStartTime > shuntReloadTime))
    {
        shuntStartTime = clock.getCurrentTime();
        shunting=true;
        steering = false;

        NxReal angle = 0;
        NxVec3 newDir(0,0,0);
        NxVec3 shuntValue = actor->getGlobalOrientation()*NxVec3(0,0,-shuntPower);
        NxVec3 carDir;

        if(actor->getLinearVelocity().magnitude() < 1)
            carDir = actor->getGlobalOrientation()*NxVec3(1,0,0);
        else
            carDir = actor->getLinearVelocity();

        newDir.add(carDir,shuntValue);
        angle = acos(newDir.dot(carDir) / (newDir.magnitude()*carDir.magnitude()));
        
        unsigned size = getDriveWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getDriveWheels()->at(i)->setSteerAngle(angle);

        size = getSteerWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getSteerWheels()->at(i)->setSteerAngle(angle);

        size = getPassiveWheels()->size();
        for(unsigned i = 0;i<size;i++)
            getPassiveWheels()->at(i)->setSteerAngle(angle);

        actor->setLinearVelocity(newDir);
    }
}

void Entity::deshunt()
{
    NxVec3 carVel = actor->getLinearVelocity();
    NxVec3 carDir = actor->getGlobalOrientation()*NxVec3(1,0,0);

    carVel.normalize(); 
    carDir.normalize(); 
    NxReal angle = acos(carVel.dot(carDir));    

    actor->setLinearVelocity(carDir*(actor->getLinearVelocity().magnitude()*cos(angle)));

    steering = true;
    shunting = false;

    for(unsigned i = 0;i<getPassiveWheels()->size();i++)
        getPassiveWheels()->at(i)->setSteerAngle(0);
}

void Entity::addSteerWheel(NxWheelShape* wheel)
{
    steerWheels.push_back(wheel);
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
    if(shunting && clock.getCurrentTime() - shuntStartTime > maxShuntTime)
        deshunt();

    if(steering)
    {
        float maxDeltaAngle = 0;
        float steeringAngle = 0;

        steeringAngle = convertVel(getActor()->getLinearVelocity().magnitude()) * percent;

        for (unsigned i = 0; i < steerWheels.size(); ++i)
            steerWheels[i]->setSteerAngle(steeringAngle);
    }
}

void Entity::chargeBattery()
{
	if(!batteryCharged && !shunting)
	{
		batteryCharged = true;
		NxVec3 lin_vel = actor->getLinearVelocity();
		NxReal speed = lin_vel.magnitude();
		lin_vel.setMagnitude(speed/2.0f);
		charge = lin_vel.magnitude();
	
		actor->setLinearVelocity(lin_vel);
	}
}

void Entity::collide(Entity* e)
{
    CustomData* cd = (CustomData*) e->getActor()->userData;
    if (cd->type == CustomData::OBSTACLE)
    {
        if(!shield)
        {
            if (cd->pickupType == MISSILE)
            {
                //Knock the car into the air
                actor->addForce(NxVec3(0,1000000,0));

                //Slow the player down by 30%
                NxVec3 unitDir = actor->getLinearVelocity();
                float vel = actor->getLinearVelocity().magnitude();
                unitDir.normalize();
                actor->setLinearVelocity((vel*0.7f)*unitDir);
            }
            else if(cd->pickupType == BARRIER)
            {
                //Slow the player down by 70%
                NxVec3 unitDir = actor->getLinearVelocity();
                float vel = actor->getLinearVelocity().magnitude();
                unitDir.normalize();
                actor->setLinearVelocity((vel*0.3f)*unitDir);
            }
        }
        else
            setShield(false);
    }
    else if(cd->type == CustomData::CAR && e->isShunting() && !isShunting()) //If both cars are shunting it will cancel the effect
    {
        NxVec3 dir = (actor->getGlobalPosition() - e->getActor()->getGlobalPosition());        
        actor->addForce(dir * 1000000);

        NxVec3 unitDir = actor->getLinearVelocity();
        float vel = actor->getLinearVelocity().magnitude();
        unitDir.normalize();
        actor->setLinearVelocity((vel*0.7f)*unitDir);
    }
}

void Entity::dischargeBattery()
{
	if(batteryCharged && !shunting)
	{
		batteryCharged = false;
        NxVec3 dir = actor->getGlobalOrientation() * NxVec3(1,0,0);
		NxVec3 lin_vel = actor->getLinearVelocity();

		//NxReal speed = lin_vel.magnitude();
		//lin_vel.setMagnitude(speed + charge);

		actor->setLinearVelocity(lin_vel + dir*charge);
	}
}

bool Entity::isShunting()
{
    return shunting;
}

bool Entity::isBatteryCharged()
{
    return batteryCharged;
}

NxActor* Entity::getActor()
{
    return actor;
}

ObjModel* Entity::getModel()
{
    return model;
}

std::vector<NxWheelShape*>* Entity::getSteerWheels()
{
    return &steerWheels;
}

std::vector<NxWheelShape*>* Entity::getDriveWheels()
{
    return &driveWheels;
}

std::vector<NxWheelShape*>* Entity::getPassiveWheels()
{
    return &passiveWheels;
}

void Entity::setUsingDisplayList(bool status)
{
    usingDisplayList = status;
}

int Entity::getDisplayListIndex()
{
    return displayListIndex;
}
bool Entity::getUsingDisplayList()
{
    return usingDisplayList;
}
void Entity::setDisplayListIndex(int index)
{
    setUsingDisplayList(true);
    displayListIndex = index;
}
void Entity::setActor(NxActor* a)
{
    if(a != NULL)
    {
        CustomData* cd = (CustomData*) a->userData;
        if(cd != NULL)
            cd->entity = this;
    }
    actor = a;
}

void Entity::setCustomData(CustomData* cd)
{
    cd->entity = this;
    actor->userData = cd;
}

bool Entity::getShield()
{
    return shield;
}

void Entity::setShield(bool active)
{
    if(active)
        shieldActivatedTime = clock.getCurrentTime();
    shield = active;
}

void Entity::setModel(ObjModel* m)
{
    model = m;
}
