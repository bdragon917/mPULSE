#pragma once
//#include "EntityComponent.h"
#include <vector>
#include "..\GameStates\Camera.h"
#include "../ModelLoader/ObjModel.h"
#include "RenderableComponent.h"
#include "NxPhysics.h"

class Entity
{
public:
    Entity();
    Entity(NxActor* a);
    //std::vector<EntityComponent*> components;
    Camera* aCam;    
    //void addComponent(EntityComponent* com);
    void addDriveWheel(NxWheelShape* wheel);
    void addPassiveWheel(NxWheelShape* wheel);
    void addTorque(int tmpTorque);
	void brake(int tmpTorque);
    void addSteeringAngle(float angle);
    //void setModel(ObjModel* m);
    void setActor(NxActor* a);    
    int getTorque();
    int getSteering();
    //ObjModel* getModel();
	NxActor* getActor();

    //Drawing stuff
    //list of renderableElements [model index, texture index]
    std::vector<RenderableComponent*> rc;
    //NxVec3 location for rendering
    //int rotation mode
    //rotation data

private:
    int torque;
    int maxTorque;
    int minTorque;
    float maxSteeringAngle;
    float maxSteeringRight;
    float maxSteeringLeft;
    float steeringAngle;

	NxActor* actor;
    ObjModel* model;
    std::vector<NxWheelShape*> driveWheels;
    std::vector<NxWheelShape*> passiveWheels;   
};