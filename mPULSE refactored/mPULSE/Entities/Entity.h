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
    void setWheel1(NxWheelShape* wheel1);
	void setWheel2(NxWheelShape* wheel2);
    void setWheel3(NxWheelShape* wheel3);
	void setWheel4(NxWheelShape* wheel4);
	NxWheelShape* getWheel1();
	NxWheelShape* getWheel2();
    NxWheelShape* getWheel3();
	NxWheelShape* getWheel4();
    
    void setModel(ObjModel* m);
    void setActor(NxActor* a);
	ObjModel* getModel();
	NxActor* getActor();

private:
    //std::vector<EntityComponent*> components;
    //Vec force
	NxActor* actor;
    ObjModel* model;
	NxWheelShape* aWheel1;
    NxWheelShape* aWheel2;
    NxWheelShape* aWheel3;
	NxWheelShape* aWheel4;
    
};