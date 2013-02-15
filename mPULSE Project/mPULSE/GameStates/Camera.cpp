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
        targetDistance = 5.0f;
        maxDistance = 20.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        userCamControl = NxVec3(0,0,0);
        targetActor = NULL;
}


Camera::Camera(NxActor* aActor)
{
        AttachtoCar(aActor);
        EquilbriumSpeed = 0.5f;
        targetDistance = 5.0f;
        maxDistance = 10.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        userCamControl = NxVec3(0,0,0);
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

void Camera::setUserCamControl(NxVec3 uControl)
{
    userCamControl = uControl;
}

void Camera::updateCamera(float dt)
{
    int mode = 0;       //Testing different camera styles here, change to different values for different test code

    switch (mode)
    {
        case 0:         //This is the inital camera set-up we have
            {
                float lookAhead = 20.f;
                NxVec3 ActLoc = targetActor->getGlobalPose().t;
                NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);

                NxVec3 movementVector = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
                NxMat33 actOri = targetActor->getGlobalOrientation();

                movementVector = targetActor->getGlobalOrientation() * movementVector;

                movementVector.y = 3.5f;
                movementVector = movementVector + ActLoc;   //This is the correct camera location target!!!
                


                movementVector = movementVector - curCamLoc;           //Gives a vector to that location

                float movMag = movementVector.magnitude();      //magnitude

                if (movementVector.magnitude() > 1.0f)
                {movementVector.normalize();}               //Might not do any thing, look at later...


                float catchUpSpd = 1.0f;

                if (movMag > (maxDistance / 2))               //Fun Camera 2!!!       //Used if camera is too far away
                {
                    catchUpSpd = movMag - (maxDistance / 2);
                }

    
                if (movMag > maxDistance)                                               //Used if camera is too far away
                {
                    printf("HURRY UP CAMERA!\n");
                    curCamLoc = (curCamLoc + movementVector * (movMag - maxDistance) );
                }
               // else
                {
                    curCamLoc = curCamLoc + movementVector * EquilbriumSpeed * catchUpSpd * dt * (movementVector.magnitude() * 0.4f);
                }
    
                if (userCamControl.magnitude() > 0.2f)
                {

                    //printf("UserControlRaw: %f %f %f\n",userCamControl.x,userCamControl.y,userCamControl.z);
                    //movementVector = (targetActor->getGlobalOrientation() * (uControl * targetDistance));
                    movementVector = (userCamControl * -targetDistance);
                    movementVector = targetActor->getGlobalOrientation() * movementVector;
                    movementVector = movementVector + ActLoc;

                    //printf("UserControl: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);

                    curCamLoc = movementVector;
                }
    

                curCamLoc.y = 3.5f + ActLoc.y;


                NxVec3 toLA = curCamLookAt - targetLookAt;
                curCamLookAt = curCamLookAt - (toLA / 4);

                break;
            }





        case 1:
            {
                float elapsed = dt * 3.75;


             if (dt == 0)
             {printf("Illegal timestep for camera");}


           // //UpdateWorldPositions();
            // Construct a matrix to transform from object space to worldspace
            // NxVec3 chaseDirection = NxVec3(-1.0f,0.0f,0.0f);
            // NxVec3 Up = NxVec3(0,1.0f,0.0f);
            // NxVec3 Right = Up.cross(chaseDirection);

            //Matrix transform = Matrix.Identity;
            //transform.Forward = ChaseDirection;
            //transform.Up = Up;
            //transform.Right = Vector3.Cross(Up, ChaseDirection);

            // Calculate desired camera properties in world space
            //desiredPosition = ChasePosition +
            //    Vector3.TransformNormal(DesiredPositionOffset, transform);
            //lookAt = ChasePosition +
            //    Vector3.TransformNormal(LookAtOffset, transform);

            //float elapsed = (float)gameTime.ElapsedGameTime.TotalSeconds;

             //Calculate where to look
             float lookAhead = 20.f;
                NxVec3 ActLoc = targetActor->getGlobalPose().t;
                NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);


            //Calcuate where to go
//             NxVec3 ActLoc = targetActor->getGlobalPose().t;
             NxVec3 tarCamLoc = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
                NxMat33 actOri = targetActor->getGlobalOrientation();

                tarCamLoc = targetActor->getGlobalOrientation() * tarCamLoc;

                tarCamLoc.y = 3.5f;
                tarCamLoc = tarCamLoc + ActLoc; //This is the correct camera location target!!!
                                   



            float stiffness = 1800.0f;
            float damping = 600.0f;
            float mass = 50.0f;

            NxVec3 velocity = targetActor->getLinearVelocity();

            // Calculate spring force
            NxVec3 stretch = curCamLoc - tarCamLoc;//position - desiredPosition;
            NxVec3 force = -stiffness * stretch - damping * velocity;


            // Apply acceleration
            NxVec3 acceleration = force / mass;
            velocity += acceleration * elapsed;

            // Apply velocity
            //curCamLoc += velocity * elapsed;
            curCamLoc = tarCamLoc;
            curCamLookAt = targetLookAt;

                break;
            }
   }






    /**
    //Camera should be targetDistance away, in negative targetActor.orientation direction
    //NxVec3 movementVector = NxVec3(0,0,-targetDistance);      //Where the camera should end up at in local space

    //targetActor->getGlobalPosition();
   // movementVector = (targetActor->getGlobalOrientation() * movementVector);    //This is now the location where the camera should be

   // movementVector = movementVector - targetActor->getGlobalPose().t;           //Gives a vector to that location

   // movementVector.normalize();

    //curCamLoc = curCamLoc + movementVector * EquilbriumSpeed;

    float lookAhead = 20.f;
    NxVec3 ActLoc = targetActor->getGlobalPose().t;
    NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);


   // NxVec3 movementVector = NxVec3(ActLoc.x,0,ActLoc.z + 15.0f);      //Where the camera should end up at in local space

     //NxVec3 movementVector = NxVec3(-1.0f,0,0.0f);      //Where the camera should end up at in local space
    NxVec3 movementVector = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
    NxMat33 actOri = targetActor->getGlobalOrientation();


    movementVector = targetActor->getGlobalOrientation() * movementVector;
    //movementVector = movementVector * targetDistance;

    movementVector = movementVector + ActLoc;
    movementVector.y = 3.5f;                    //This is the correct camera location target!!!


    //printf("TargetLocation: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);
    
    //movementVector = movementVector - targetActor->getGlobalPose().t;           //Gives a vector to that location
    movementVector = movementVector - curCamLoc;           //Gives a vector to that location

    float movMag = movementVector.magnitude();      //magnitude

    if (movementVector.magnitude() > 1.0f)
    {movementVector.normalize();}               //Might not do any thing, look at later...

   
   // printf("Vector: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);

    //printf("CamLocation: %f %f %f\n", curCamLoc.x, curCamLoc.y, curCamLoc.z);


    float catchUpSpd = 1.0f;

    if (movMag > (maxDistance / 2))               //Fun Camera 2!!!       //Used if camera is too far away
    {
        catchUpSpd = movMag - (maxDistance / 2);
    }

    
    if (movMag > maxDistance)                                               //Used if camera is too far away
    {
        printf("HURRY UP CAMERA!\n");
        curCamLoc = (curCamLoc + movementVector * (movMag - maxDistance) );
    }
   // else
    {
        curCamLoc = curCamLoc + movementVector * EquilbriumSpeed * catchUpSpd * dt * (movementVector.magnitude() * 0.4f);
    }
    
    if (userCamControl.magnitude() > 0.2f)
    {

        //printf("UserControlRaw: %f %f %f\n",userCamControl.x,userCamControl.y,userCamControl.z);
        //movementVector = (targetActor->getGlobalOrientation() * (uControl * targetDistance));
        movementVector = (userCamControl * -targetDistance);
        movementVector = targetActor->getGlobalOrientation() * movementVector;
        movementVector = movementVector + ActLoc;

        //printf("UserControl: %f %f %f\n", movementVector.x, movementVector.y, movementVector.z);

        curCamLoc = movementVector;
    }
    

    //curCamLoc.x = movementVector.x;
    //curCamLoc.z = movementVector.z;
    curCamLoc.y = 3.5f + ActLoc.y;

    //curCamLookAt = ActLoc;
    //f=kx
    NxVec3 toLA = curCamLookAt - targetLookAt;
    curCamLookAt = curCamLookAt - (toLA / 4);
    //curCamLookAt = targetLookAt;

    if (movMag > (maxDistance / 2))
    {

 //       printf("Camera is more than MaxDistance!!!");
        //Move camera towards point faster!
    }
    */
}