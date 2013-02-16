#pragma once

#include <NxPhysics.h>
#include <stdio.h>

class Camera
{
public:
    Camera();
    Camera(NxActor* aActor);
    
    ~Camera();


        void AttachtoCar(NxActor* aActor);
        NxVec3 getLookAt();
        NxVec3 getCamLoc();
        void setUserCamControl(NxVec3 userControl);
        void setDistance(float inDistance);
        void setMaxDistance(float inDistance);
        void updateCamera(float dt);
        void resetCamera();

private:
        float EquilbriumSpeed;  //Should be between 0 and 1
        float targetDistance;
        float maxDistance;
        NxVec3 curCamLoc;
        NxVec3 lastCamLoc;
        NxVec3 curCamLookAt;
        NxVec3 curOrientation;
        NxActor* targetActor;

        NxVec3 userCamControl;

        //For field of view (TO BE IMPLIMENTED)
        double nearVal;
        double farVal;


};
