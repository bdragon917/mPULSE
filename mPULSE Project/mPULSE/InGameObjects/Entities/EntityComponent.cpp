#include <InGameObjects/Entities/EntityComponent.h>

EntityComponent::EntityComponent(void)
{
}

NxActor* EntityComponent::getActor()
{
    return actor;
}

ObjModel* EntityComponent::getModel()
{
    return model;
}

void EntityComponent::setModel(ObjModel* m)
{
    model = m;
}

void EntityComponent::setActor(NxActor* a)
{
    actor = a;
}
