#pragma once

#include <NxPhysics.h>
#include <stdio.h>
#include "../AI/Waypoint.h"
#include "CustomData.h"
#include "Entities\Entity.h"
#include "SoundEngine\SoundEngine.h"
#include "EventManager/SoundEvent.h"
#include "EventManager/CollisionEvent.h"
#include "EventManager/WaypointEvent.h"
#include "EventManager/EventManager.h"
#include "GameStates\GameVariables.h"

class TriggerCallback : public NxUserTriggerReport 
{
public:
	TriggerCallback(void);
	~TriggerCallback(void);
	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);

private:
    GameVariables* gameVariables;
    SoundEngine* soundEngine;
};

