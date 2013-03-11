#include <InGameObjects/TriggerCallback.h>

TriggerCallback::TriggerCallback(void)
{
    soundEngine = SoundEngine::getInstance();
}


TriggerCallback::~TriggerCallback(void)
{
}

void TriggerCallback::onTrigger(NxShape& triggerShape, NxShape& actingShape, NxTriggerFlag status)
{
	if((status & NX_TRIGGER_ON_ENTER) && (triggerShape.getType() == NX_SHAPE_BOX)) 
	{
		NxActor& triggerActor = triggerShape.getActor();
        NxActor& actingActor = actingShape.getActor();

		if(triggerActor.userData != NULL && actingActor.userData != NULL)
        {
            CustomData* triggerCd = (CustomData*)triggerActor.userData;            
            CustomData* actingCd = (CustomData*)actingActor.userData;

            if (actingCd->type == CustomData::CAR)
            {
                //Waypoints
                if(triggerCd->type == CustomData::WAYPOINT)
                {
                    if(actingCd->wp->nextId == triggerCd->wp->id) //check if the car hit the next valid waypoint
					{
						if(actingCd->wp->id > triggerCd->wp->id)  //check if the car passed the finish line 
                        {
                            actingCd->laps++;
                            if(actingCd->laps > 1)                                
                                printf("You Win!");
                        }
                        actingCd->wp = actingCd->wp->nextWaypoint;
					}
                }              
                //if ((actingCd->type == actingCd->OBSTACLE) && (actingCd->pickupType == 0))    //Missile on Car
                //{
                //    triggerShape.getActor().addForce(NxVec3(0,50000,0));  //should go up, and slow down
                //    soundEngine->crashed(0);
                //    actingShape.getActor().getScene().releaseActor(triggerActor);
                //}
                //if ((actingCd->type == actingCd->OBSTACLE) && (actingCd->pickupType == 1))    //Shield vs car
                //{
                //    
                //}
                //if ((actingCd->type == actingCd->CAR) && (triggerCd->pickupType == 2))    //Barrier vs car
                //{
                //    actingShape.getActor().setLinearVelocity(actingShape.getActor().getLinearVelocity() * 0.3f);
                //    soundEngine->crashed(0);
                //}
            }
        }
        else
            printf("TriggerCallback: actingActor.userData = NULL!\n");		
	}
	else if((status & NX_TRIGGER_ON_ENTER) && (triggerShape.getType() == NX_SHAPE_SPHERE)) 
	{
        NxActor& triggerActor = triggerShape.getActor();
        CustomData* triggerCd = (CustomData*)triggerActor.userData;

        NxActor& actingActor = actingShape.getActor();
        CustomData* actingCd = (CustomData*)actingActor.userData;
        actingCd->pickupType = triggerCd->pickupType;

		printf("got %i\n",actingCd->pickupType);        //Power-Up picked up
        soundEngine->crashed(1);
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
