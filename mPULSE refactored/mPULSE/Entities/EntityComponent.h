#pragma once
#include "../ModelLoader/ObjModel.h"
#include "NxPhysics.h"

class EntityComponent
{

public:
    EntityComponent();
    NxActor* EntityComponent::getActor();
    ObjModel* EntityComponent::getModel();
    void setModel(ObjModel* m);
    void setActor(NxActor* a);

private:
    NxActor* actor;
    ObjModel* model;

};

