#pragma once
#include "InGameObjects\Entities\Entity.h"
#include "SoundEvent.h"
#include "CollisionEvent.h"
#include "TriggerEvent.h"
#include "WaypointEvent.h"
#include <vector>

class EventManager
{
public:
    
    static EventManager* getInstance();
    void clearAllEvents();
    void addEvent(SoundEvent* e);
    void addEvent(CollisionEvent* e);
    void addEvent(WaypointEvent* e);
    void addEvent(TriggerEvent* e);

    std::vector<SoundEvent*>* getSoundEvents();
    std::vector<CollisionEvent*>* getCollisionEvents();
    std::vector<WaypointEvent*>* getWaypointEvents();
    std::vector<TriggerEvent*>* getTriggerEvents();

private:
    EventManager();
    std::vector<SoundEvent*> soundEvents;
    std::vector<CollisionEvent*> collisionEvents;
    std::vector<WaypointEvent*> waypointEvents;
    std::vector<TriggerEvent*> triggerEvents;
};

