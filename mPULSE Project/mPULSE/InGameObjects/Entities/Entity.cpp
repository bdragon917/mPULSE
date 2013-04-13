#include <InGameObjects/Entities/Entity.h>

Entity::Entity(int tmpTimeToLive, NxActor* a, ObjModel* tmpModel)
{
    rank = 0;
    alive = true;
	batteryCharged = false;
    usingDisplayList = false;
    steering = true;
    shunting = false;
    boosting = false;
    batteryCharging = false;
    batteryDischarging = false;
	obs = 0; //money earned from current race.
	highSpeedObsTime = 0;

    tiltAngle = 0.0f;   //used in rendering for Tilt

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

    boostAmount = 0;
    shuntStartTime = 0;
    shieldActivatedTime = 0;
    shieldTimeout = 10000;
    maxShuntTime = 200;
    shuntPower = 50;
    shuntReloadTime = 600;
    delayBeforeTracking = 1000;
    boostPeriod = 500;
    chargePeriod = 450;
    rankingName = "not set";

    timeToLive = tmpTimeToLive;
    timeCreated = clock.getCurrentTime();

    tracker = NULL;
    tracking = NULL;

    if(actor != NULL)
    {
        CustomData* cd = (CustomData*) actor->userData;
        if(cd != NULL)
            cd->entity = this;
    }
}

void Entity::applyDischargeBattery()
{
    unsigned dt = clock.getDeltaTime(dischargeStartTime);

    if(dt > chargePeriod)
        dt = chargePeriod;

    NxVec3 dir = actor->getGlobalOrientation().getColumn(0);
    NxReal chargePercent = sin(((float)dt/(float)chargePeriod) * 1.570796327f);
    NxReal chargeVal = chargeAmount * chargePercent;

	NxVec3 lin_vel = actor->getLinearVelocity();
	actor->setLinearVelocity(lin_vel + dir*chargeVal);

    chargeAmount -= chargeVal;

    if(dt >= chargePeriod)
    {
        batteryDischarging  = false;
        batteryCharged = false;
    }
}

void Entity::applyChargeBattery()
{
    unsigned dt = clock.getDeltaTime(chargeStartTime);
    if(dt > chargePeriod)
        dt = chargePeriod;

    NxVec3 dir = actor->getGlobalOrientation().getColumn(0);
    NxReal chargePercent = sin(((float)dt/(float)chargePeriod) * 1.570796327f);
    NxReal chargeVal = chargeAmount * chargePercent;

	NxVec3 lin_vel = actor->getLinearVelocity();
	actor->setLinearVelocity(lin_vel - dir*chargeVal);

    chargeAmount -= chargeVal;

    if(dt >= chargePeriod)
    {
        batteryCharging  = false;
        batteryCharged = true;
    }
}

void Entity::applyBoost()
{
    unsigned dt = clock.getDeltaTime(boostStartTime);
    if(dt > boostPeriod)
        dt = boostPeriod;

    NxVec3 dir = actor->getGlobalOrientation().getColumn(0);
    NxReal boostPercent = sin(((float)dt/(float)boostPeriod) * 1.570796327f);
    NxReal boostVal = boostAmount * boostPercent;
	NxVec3 lin_vel = actor->getLinearVelocity();
	actor->setLinearVelocity(lin_vel + dir*boostVal);
    boostAmount -= boostVal;

    if(dt >= boostPeriod)
        boosting = false;
}

void Entity::update()
{
    if(boosting)        
        applyBoost();
    if(batteryCharging)
        applyChargeBattery();
    else if(batteryDischarging)
        applyDischargeBattery();

    if (clock.getCurrentTime() - shieldActivatedTime > shieldTimeout)
        shield = false;

    if(tracking != NULL && clock.getCurrentTime() > timeCreated+delayBeforeTracking)
    {
        //Update the velocity
        NxVec3 myPos = actor->getGlobalPosition();
        NxVec3 trackingPos = tracking->getActor()->getGlobalPosition();
        NxVec3 dirToTarget = trackingPos - myPos;   
        dirToTarget.normalize();

        NxReal velMag = actor->getLinearVelocity().magnitude();
        actor->setLinearVelocity(velMag*dirToTarget);

        //Update the orientation        
        NxMat33 orientation = actor->getGlobalOrientation();
        orientation.setColumn(0,dirToTarget);
        actor->setGlobalOrientation(orientation);
    }
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
    if(tracking != NULL)
        tracking->tracker = NULL;

    if(tracker != NULL)
        tracker->tracking = NULL;

    alive = false;
    timeToLive = 0;
}

bool Entity::isAlive()
{
    if(alive)
    {
        if(timeToLive==-1)
            alive = true;    
        else if((int)clock.getCurrentTime() - timeCreated >= timeToLive)
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

NxSweepQueryHit* Entity::linearSweep(float dt)
{
	NxU32 flags = NX_SF_STATICS;
    NxSweepQueryHit* result = new NxSweepQueryHit();
	
    NxVec3* impactPoint = NULL;
	NxVec3 vec = actor->getLinearVelocity()*(dt/1000.0f);
	if(actor->linearSweep(vec, flags, NULL, 1, result, NULL) > 0)
	{
		return result;
	}
	return NULL;
}

Entity::PickupType Entity::usePickup()
{
    CustomData* cd = (CustomData*) actor->userData;
    int type = cd->pickupType;   

    if(type != 3 || !shunting)
        cd->pickupType = -1;

    if(type == 0)
        return MISSILE;
    else if(type == 1)
        return SHIELD;
    else if(type == 2)
        return BARRIER; 
    else if(type == 3 && !shunting)
        return BOOST;
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
    float sensitivity = 12.0;

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

float Entity::raceWinnings()
{
	return (float)obs;
}

void Entity::highSpeedCash()
{
	NxWheelContactData nxwcd; 
    driveWheels[0]->getContact(nxwcd);

	if (driveWheels[0]->getContact(nxwcd) != NULL)
	{
		if (actor->getLinearVelocity().magnitude() > 100.0f)
		{
			if (clock.getCurrentTime() - highSpeedObsTime > 2500)
			{
				obs = obs + 100;
				highSpeedObsTime = clock.getCurrentTime();
			}
		}
	}
}

void Entity::boost()
{        
    boosting = true;
    boostAmount = 50;
    boostStartTime = clock.getCurrentTime();
}

void Entity::missleCash()
{
	obs = obs + 500;
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

				//e->missleCash();
				//obs = obs + 500;
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

bool Entity::getBatteryCharged()
{
    return batteryCharged;
}

void Entity::chargeBattery()
{
	if(!batteryCharged && !shunting && !batteryCharging)
	{
        chargeStartTime = clock.getCurrentTime();
        batteryCharging = true;

		NxVec3 lin_vel = actor->getLinearVelocity();
		NxReal speed = lin_vel.magnitude();
        chargeAmount = speed/2.0f;
        charge = chargeAmount;
	}
}

void Entity::dischargeBattery()
{
	if(batteryCharged && !shunting && !batteryCharging && !batteryDischarging)
	{                
        dischargeStartTime = clock.getCurrentTime();
        batteryDischarging = true; 
        chargeAmount = charge;
        charge = 0;
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

bool Entity::getSweepCollision()
{
	return sweepCollision;
}

void Entity::setSweepCollision(bool b)
{
	sweepCollision = b;
}

NxVec3 Entity::getImpactPoint()
{
	return impactPoint;
}

void Entity::setImpactPoint(NxVec3 point)
{
	impactPoint = point;
}

NxVec3 Entity::getImpactNormal()
{
	return impactNormal;
}

void Entity::setImpactNormal(NxVec3 normal)
{
	impactNormal = normal;
}

NxVec3 Entity::getOldVelocity()
{
	return oldVelocity;
}

void Entity::setOldVelocity(NxVec3 vel)
{
	oldVelocity = vel;
}

NxReal Entity::getDotResult()
{
	return dotResult;
}

void Entity::setDotResult(NxReal result)
{
	dotResult = result;
}

void Entity::setModel(ObjModel* m)
{
    model = m;
}
