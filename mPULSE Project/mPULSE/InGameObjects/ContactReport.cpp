#include "ContactReport.h"

ContactReport::ContactReport(void)
{
}


ContactReport::~ContactReport(void)
{
}

void ContactReport::onContactNotify(NxContactPair& pair, NxU32 events)
{
    EventManager* eventManager = EventManager::getInstance();

    NxActor* actor1 = NULL;
    NxActor* actor2 = NULL;
    CustomData* actor1CustomData = NULL;
    CustomData* actor2CustomData = NULL;

    if(!(pair.isDeletedActor[0] || pair.isDeletedActor[1]))
    {
        actor1 = pair.actors[0];
        actor2 = pair.actors[1];
        if(NX_NOTIFY_ON_START_TOUCH & events)
        {
            actor1CustomData = (CustomData*)actor1->userData;
            actor2CustomData = (CustomData*)actor2->userData;

            if(actor1CustomData->type == CustomData::OBSTACLE && actor2CustomData->type == CustomData::CAR)
            {
                if(actor1CustomData->pickupType == 0) //Car hit a missile
                {
                    eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_FIRST));
                }
                else if(actor1CustomData->pickupType == 2) //Car hit a barrier
                {
                    eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_FIRST));
                }
            }
            else if(actor1CustomData->type == CustomData::CAR && actor2CustomData->type == CustomData::CAR)
            {
                eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_NONE));
            }
            else if(actor1CustomData->type == CustomData::OBSTACLE && actor2CustomData->type == CustomData::OBSTACLE)
            {
                if(actor1CustomData->pickupType == 0 || actor2CustomData == 0) //If a missile is involved destroy both obstacles
                    eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_BOTH));
            }
        }
    }
}

void printType()
{

}