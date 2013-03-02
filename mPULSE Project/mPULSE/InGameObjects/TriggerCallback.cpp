#include "TriggerCallback.h"


TriggerCallback::TriggerCallback(void)
{
}


TriggerCallback::~TriggerCallback(void)
{
}



void TriggerCallback::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
{
	if((status & NX_TRIGGER_ON_ENTER) && (triggerShape.getType() == NxShapeType::NX_SHAPE_BOX)) 
	{
		NxActor& triggerActor = triggerShape.getActor();

		if(triggerActor.userData != NULL) {
			Waypoint* wp = (Waypoint*)triggerActor.userData;
			printf("Waypoint ID: %i\n", wp->id);
		}
		
	}
	else if((status & NX_TRIGGER_ON_ENTER) && (triggerShape.getType() == NxShapeType::NX_SHAPE_SPHERE)) 
	{
		printf("ITS A SPHERE!");
	}
	/*
	if(status & NX_TRIGGER_ON_ENTER)
	{
		//A body entered the trigger area for the first time
		printf("Entered Trigger\n");
	}
	if(status & NX_TRIGGER_ON_LEAVE)
	{
		//A body left the trigger area
		printf("Left Trigger\n");
	}
	//Should not go negative
	//NX_ASSERT(gNbTouchedBodies>=0);
	*/
}
