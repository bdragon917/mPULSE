#pragma once

#include <NxPhysics.h>
#include <stdio.h>

class TriggerCallback : public NxUserTriggerReport 
{
public:
	TriggerCallback(void);
	~TriggerCallback(void);
	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
};

