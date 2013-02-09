#include "Camera.h"

/**
        void AttachtoCar(NxActor* aActor);
        NxVec3 getLookAt();
        NxVec3 getCamLoc();
        void setDistance();

private:

        float EquilbriumSpeed;
        float targetDistance;
        NxVec3 curCamLoc;
        NxVec3 curOrientation;
        NxActor* targetActor;
        **/
Camera::Camera(void)
{
        EquilbriumSpeed = 0.1f;
        targetDistance = 2.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        targetActor = NULL;
}

Camera::Camera(NxActor* aActor)
{
        AttachtoCar(aActor);
        Camera();
}

Camera::~Camera(void)
{
}

void Camera::AttachtoCar(NxActor* aActor)
{
        targetActor = aActor;
}

NxVec3 Camera::getLookAt()
{
        return curCamLookAt;
}

NxVec3 Camera::getCamLoc()
{
    return curCamLoc;
}

void Camera::setDistance(float inDistance)
{
    targetDistance = inDistance;
}

void Camera::setMaxDistance(float inDistance)
{
    maxDistance = inDistance;
}

void Camera::updateCamera()
{
    //Camera should be targetDistance away, in negative targetActor.orientation direction
    NxVec3 movementVector = NxVec3(0,0,-targetDistance);      //Where the camera should end up at in local space

    //targetActor->getGlobalPosition();
    movementVector = (targetActor->getGlobalOrientation() * movementVector);    //This is now the location where the camera should be

    movementVector = movementVector - targetActor->getGlobalPose().t;           //Gives a vector to that location

    movementVector.normalize();

    curCamLoc = curCamLoc + movementVector * EquilbriumSpeed;

    if ((curCamLoc - targetActor->getGlobalPose().t).distance(NxVec3(0,0,0)) > maxDistance)
    {
        printf("Camera is more than MaxDistance!!!");
        //Move camera towards point faster!
    }
}