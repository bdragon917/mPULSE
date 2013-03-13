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

    if(!pair.isDeletedActor[0] && !pair.isDeletedActor[1])
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
                    //Knock the car into the air
                    actor2->addForce(NxVec3(0,1000000,0));

                    //Slow the player down by 30%
                    NxVec3 unitDir = actor2->getLinearVelocity();
                    float vel = actor2->getLinearVelocity().magnitude();
                    unitDir.normalize();
                    actor2->setLinearVelocity((vel*0.7f)*unitDir);
                    //actor1->raiseActorFlag(NX_AF_DISABLE_COLLISION);

                    eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_FIRST));
                }
                else if(actor1CustomData->pickupType == 2) //Car hit a barrier
                {
                    //Slow the player down by 70%
                    NxVec3 unitDir = actor2->getLinearVelocity();
                    float vel = actor2->getLinearVelocity().magnitude();
                    unitDir.normalize();
                    actor2->setLinearVelocity((vel*0.3f)*unitDir);
                    //actor1->raiseActorFlag(NX_AF_DISABLE_COLLISION);

                    eventManager->addEvent(new CollisionEvent(actor1CustomData->entity,actor2CustomData->entity, CollisionEvent::DESTROY_FIRST));
                }
            }
        }
    }
}

void printType()
{

}