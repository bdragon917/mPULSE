#pragma once
#include "nxusercontactreport.h"
#include "EventManager/SoundEvent.h"
#include "EventManager/CollisionEvent.h"
#include "EventManager/WaypointEvent.h"
#include "EventManager/EventManager.h"
#include "CustomData.h"
#include "stdio.h"
#include "NxActor.h"

class ContactReport : public NxUserContactReport
{
public:
    ContactReport(void);
    ~ContactReport(void);
    void onContactNotify(NxContactPair& pair, NxU32 events);
};

