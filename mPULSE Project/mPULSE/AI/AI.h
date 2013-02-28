#pragma once
#define NOMINMAX
#include "../Input/XboxController.h"
#include <NxPhysics.h>
#include <NxActor.h>
//#include "../Entities/Entity.h"

class AI
{
public:
    AI(void);
    ~AI(void);

    XboxController* getControl();
    void update();

private:


    NxActor* myActor;
    NxVec3 myLocation;
    NxVec3 myOrientation;
};

