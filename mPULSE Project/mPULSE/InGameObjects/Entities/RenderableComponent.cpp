#include <InGameObjects/Entities/RenderableComponent.h>

RenderableComponent::RenderableComponent(int newModelIndex, int newTextureIndex)
{
    modelID = newModelIndex;
    textureID = newTextureIndex;
}

RenderableComponent::~RenderableComponent()
{
}