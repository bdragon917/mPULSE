#include "EventManager.h"


EventManager* EventManager::getInstance()
{
    static EventManager eventManager;
    return &eventManager;
}

EventManager::EventManager()
{

}

void EventManager::clearAllEvents()
{
    soundEvents.clear();
    collisionEvents.clear();
    waypointEvents.clear();

    soundEvents.shrink_to_fit();
    collisionEvents.shrink_to_fit();
    waypointEvents.shrink_to_fit();
}

void EventManager::addEvent(SoundEvent* e)
{ 
    soundEvents.push_back(e);
}
void EventManager::addEvent(CollisionEvent* e)
{ 
    collisionEvents.push_back(e);
}
void EventManager::addEvent(WaypointEvent* e)
{
    waypointEvents.push_back(e);
}

void EventManager::addEvent(TriggerEvent* e)
{
    triggerEvents.push_back(e);
}

std::vector<TriggerEvent*>* EventManager::getTriggerEvents()
{
    return &triggerEvents;
}

std::vector<SoundEvent*>* EventManager::getSoundEvents()
{
    return &soundEvents;
}

std::vector<CollisionEvent*>* EventManager::getCollisionEvents()
{
    return &collisionEvents;
}

std::vector<WaypointEvent*>* EventManager::getWaypointEvents()
{
    return &waypointEvents;
}