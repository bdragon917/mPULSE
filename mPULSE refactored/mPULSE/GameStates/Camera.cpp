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
        EquilbriumSpeed = 0.5f;
        targetDistance = 15.0f;
        maxDistance = 40.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        targetActor = NULL;
}


Camera::Camera(NxActor* aActor)
{
        AttachtoCar(aActor);
        EquilbriumSpeed = 0.5f;
        targetDistance = 15.0f;
        maxDistance = 40.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
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

void Camera::updateCamera(float dt)
{
    //Camera should be targetDistance away, in negative targetActor.orientation direction
    //NxVec3 movementVector = NxVec3(0,0,-targetDistance);      //Where the camera should end up at in local space

    //targetActor->getGlobalPosition();
   // movementVector = (targetActor->getGlobalOrientation() * movementVector);    //This is now the location where the camera should be

   // movementVector = movementVector - targetActor->getGlobalPose().t;           //Gives a vector to that location

   // movementVector.normalize();

    //curCamLoc = curCamLoc + movementVector * EquilbriumSpeed;


    NxVec3 ActLoc = targetActor->getGlobalPose().t;


   // NxVec3 movementVector = NxVec3(ActLoc.x,0,ActLoc.z + 15.0f);      //Where the camera should end up at in local space

     //NxVec3 movementVector = NxVec3(-1.0f,0,0.0f);      //Where the camera should end up at in local space
     NxVec3 movementVector = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
    NxMat33 actOri = targetActor->getGlobalOrientation();


    movementVector = targetActor->getGlobalOrientation() * movementVector;
    //movementVector = movementVector * targetDistance;

    movementVector = movementVector + ActLoc;
    movementVector.y = 3.5f;                    //This is the correct camera location target!!!


    printf("TargetLocation: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);
    
    //movementVector = movementVector - targetActor->getGlobalPose().t;           //Gives a vector to that location
    movementVector = movementVector - curCamLoc;           //Gives a vector to that location

    float movMag = movementVector.magnitude();      //magnitude

    if (movementVector.magnitude() > 1.0f)
    {movementVector.normalize();}

   
    printf("Vector: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);

    printf("CamLocation: %f %f %f\n", curCamLoc.x, curCamLoc.y, curCamLoc.z);


    float catchUpSpd = 1.0f;

    if (movMag > (maxDistance / 2))
    {
        catchUpSpd = movMag - (maxDistance / 2);
    }

    
    curCamLoc = curCamLoc + movementVector * EquilbriumSpeed * catchUpSpd * dt;


    //curCamLoc.x = movementVector.x;
    //curCamLoc.z = movementVector.z;
    curCamLoc.y = 3.5f;

    curCamLookAt = ActLoc;

    if (movMag > (maxDistance / 2))
    {

 //       printf("Camera is more than MaxDistance!!!");
        //Move camera towards point faster!
    }
}