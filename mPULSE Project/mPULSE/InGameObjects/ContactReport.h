#pragma once
#include "nxusercontactreport.h"
class ContactReport :
    public NxUserContactReport
{
public:
    ContactReport(void);
    ~ContactReport(void);
    void onContactNotify(NxContactPair& pair, NxU32 events);
};

