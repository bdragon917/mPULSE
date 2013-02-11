#pragma once
//#include "EntityComponent.h"
#include <vector>
#include "..\GameStates\Camera.h"
#include "../ModelLoader/ObjModel.h"
#include "NxPhysics.h"

class Entity
{
public:
    Entity();
    //std::vector<EntityComponent*> components;
    Camera* aCam;    
    //void addComponent(EntityComponent* com);
    void addDriveWheel(NxWheelShape* wheel);
    void addPassiveWheel(NxWheelShape* wheel);
    void addTorque(int tmpTorque);
	void brake(int tmpTorque);
    void addSteeringAngle(float angle);
    void setModel(ObjModel* m);
    void setActor(NxActor* a);    
    int getTorque();
    int getSteering();
    ObjModel* getModel();
	NxActor* getActor();

private:
    int torque;
    float steeringAngle;
	NxActor* actor;
    ObjModel* model;
    std::vector<NxWheelShape*> driveWheels;
    std::vector<NxWheelShape*> passiveWheels;   
};