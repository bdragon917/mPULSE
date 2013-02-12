#include "EntityComponent.h"


EntityComponent::EntityComponent(void)
{
}

const std::vector<NxActor>* EntityComponent::getActors()
{
    return &actors;
}

const std::vector<ObjModel>* EntityComponent::getModels()
{
    return &models;
}