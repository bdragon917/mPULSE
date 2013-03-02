#pragma once

#include <NxPhysics.h>
#include <stdio.h>
#include "../AI/Waypoint.h"
#include "CustomData.h"

class TriggerCallback : public NxUserTriggerReport 
{
public:
	TriggerCallback(void);
	~TriggerCallback(void);
	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
};

