#include <GameStates/Camera.h>
#include <iostream>

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
        targetDistance = 10.0f;
        maxDistance = 30.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        userCamControl = NxVec3(0,0,0);
        targetActor = NULL;

        xStretch = 1.0f;
        yStretch = 1.0f;


        lastCamLoc = NxVec3(-5.0f,3.5f,0);

}

Camera::Camera(NxActor* aActor)
{
        AttachtoCar(aActor);
        EquilbriumSpeed = 0.5f;
        targetDistance = 10.0f;
        maxDistance = 30.0f;
        curCamLoc = NxVec3(0,0,-1.0f);
        curCamLookAt = NxVec3(0,0,0);
        curOrientation = NxVec3(0,0,0);
        userCamControl = NxVec3(0,0,0);

        lastCamLoc = NxVec3(-5.0f,3.5f,0);

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
float Camera::getXStretch()
{
        return xStretch;
}

float Camera::getYStretch()
{
        return yStretch;
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

void Camera::resetCamera()
{
        NxMat34 actorPose = targetActor->getGlobalPose();

        curCamLoc = actorPose * NxVec3(0,0,-1.0f);
        curCamLookAt = actorPose * NxVec3(0,0,0);
        curOrientation = actorPose * NxVec3(0,0,0);
        userCamControl = NxVec3(0,0,0);
        xStretch = 1.0f;
}

void Camera::updateCamera(float dt)
{
    int mode = 4;       //Testing different camera styles here, change to different values for different test code

    //xStretch = 1.0f;
    //yStretch = 1.0f;

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

            movementVector.y = 6.5f;
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
                std::cout << "HURRY UP CAMERA!" << std::endl;
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
            float elapsed = dt * 3.75f;
            if (dt == 0.0f)
                std::cout << "Illegal timestep for camera" << std::endl;

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
            float lookAhead = 30.f;
            NxVec3 ActLoc = targetActor->getGlobalPose().t;
            NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);


            //Calcuate where to go
            //NxVec3 ActLoc = targetActor->getGlobalPose().t;
            targetDistance = 5.0f;

            NxVec3 tarCamLoc = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
            NxMat33 actOri = targetActor->getGlobalOrientation();

            tarCamLoc = targetActor->getGlobalOrientation() * tarCamLoc;

            tarCamLoc.y = 3.5f;
            tarCamLoc = tarCamLoc + ActLoc; //This is the correct camera location target!!!
                                   
            float stiffness = 12.000f;
            float damping = 4000.0f;
            float mass = 25.0f;
            //float stiffness = 1800.0f;
            //float damping = 600.0f;
            //float mass = 50.0f;

            NxVec3 velocity = (targetActor->getLinearVelocity()/1000);

            //velocity = targetActor->getCMassGlobalOrientation() * -velocity; 

            // Calculate spring force
            NxVec3 stretch = (curCamLoc - tarCamLoc);//position - desiredPosition;
            NxVec3 force = (-stiffness * stretch) - (damping * velocity);

            // Apply acceleration
            NxVec3 acceleration = force / mass;
            velocity += acceleration * elapsed;

            // Apply velocity
            curCamLoc += velocity;  // * elapsed;
            //curCamLoc = curCamLoc + (stretch * 0.5);
            //curCamLoc = tarCamLoc;
            //curCamLookAt = targetLookAt;
            curCamLookAt = targetLookAt + velocity;

            break;
        }
        case 2:     //Working fixed Camera
        {
            float elapsed = dt * 3.75f;

            if (dt == 0.0f)
                std::cout << "Illegal timestep for camera" << std::endl;

            //Calculate where to look
            float lookAhead = 40.f;
            NxVec3 ActLoc = targetActor->getGlobalPose().t;
            NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);

            //Calcuate where to go
            //NxVec3 ActLoc = targetActor->getGlobalPose().t;
            targetDistance = 8.0f;

            NxVec3 tarCamLoc = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
            NxMat33 actOri = targetActor->getGlobalOrientation();

            tarCamLoc = targetActor->getGlobalOrientation() * tarCamLoc;

            tarCamLoc.y = 3.5f;
            tarCamLoc = tarCamLoc + ActLoc; //This is the correct camera location target!!!               

            //float stiffness = 1800.0f;
            //float damping = 600.0f;
            //float mass = 50.0f;

            NxVec3 velocity = (targetActor->getLinearVelocity()/1000);

            //velocity = targetActor->getCMassGlobalOrientation() * -velocity; 

            // Calculate spring force
            //NxVec3 stretch = (curCamLoc - tarCamLoc);//position - desiredPosition;
            //NxVec3 force = (-stiffness * stretch) - (damping * velocity);

            // Apply acceleration
            //NxVec3 acceleration = force / mass;
            //velocity += acceleration * elapsed;

            // Apply velocity
            //curCamLoc += velocity;  // * elapsed;
            //curCamLoc = curCamLoc + (stretch * 0.5);
            curCamLoc = tarCamLoc;
            curCamLookAt = targetLookAt;
            //curCamLookAt = targetLookAt + velocity;

            break;
        }
        case 3:         //This is the inital camera set-up we have
        {
            float lookAhead = 20.f;
            NxVec3 ActLoc = targetActor->getGlobalPose().t;
            NxVec3 targetLookAt = ((targetActor->getGlobalOrientation() * NxVec3(lookAhead,0,0.0f) ) + ActLoc);

            NxVec3 movementVector = NxVec3(-targetDistance,0,0.0f);      //Where the camera should end up at in local space
            NxMat33 actOri = targetActor->getGlobalOrientation();

            movementVector = targetActor->getGlobalOrientation() * movementVector;

            movementVector.y = 6.5f;
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
                std::cout << "HURRY UP CAMERA!" << std::endl;
                curCamLoc = (curCamLoc + movementVector * (movMag - maxDistance) );
            }
            // else
            {

                float stiffness = 100.0f;
                float damping = 600.0f;
                float mass = 50.0f;

                NxVec3 velocity =  movementVector * movementVector.magnitude();

                    NxVec3 stretch = (curCamLoc - (curCamLoc + movementVector));//position - desiredPosition;
                    NxVec3 force = (-stiffness * stretch) - (damping * velocity);
                    


                                // Apply acceleration
                NxVec3 acceleration = force / mass;
                velocity += acceleration * dt;

                // Apply velocity
                curCamLoc += velocity;  // * elapsed;

                //curCamLoc = curCamLoc + movementVector * EquilbriumSpeed * catchUpSpd * dt * (movementVector.magnitude() * 0.4f);
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
        case 4:         //This fixes the slope issues
            {


                //Set target camera location in local space
                float disAbove = 5.0f;
                NxVec3 tarCamLoc = NxVec3(-targetDistance,disAbove,0.0f);

                //NxVec3 tarCamSpd30 = NxVec3(-targetDistance,disAbove,0.0f);
                //NxVec3 tarCamSpd50 = NxVec3(-targetDistance * 0.75f,disAbove,0.0f);
                //NxVec3 tarCamSpd70 = NxVec3(-targetDistance * 0.60f,disAbove * 0.75f,0.0f);
                NxVec3 tarCamSpd30 = NxVec3(-targetDistance * 0.80f,disAbove,0.0f);
                NxVec3 tarCamSpd50 = NxVec3(-targetDistance * 0.60f,disAbove,0.0f);
                NxVec3 tarCamSpd70 = NxVec3(-targetDistance * 0.20f,disAbove * 0.75f,0.0f);


                NxVec3 tarCamSpdH = NxVec3(-targetDistance * 0.10f,disAbove * 0.5f,0.0f);       //add random jitter

                float curActorSpd = targetActor->getLinearVelocity().magnitude();

                //Change camera location based on speed
                if (curActorSpd < 30.0f)
                {
                    tarCamLoc = (tarCamLoc * (1 - (curActorSpd/30.0f))) + (tarCamSpd30 * (curActorSpd/30.0f));
                }
                else if (curActorSpd < 50.0f)
                {
                    tarCamLoc = (tarCamSpd30 * (1 - ((curActorSpd-30.0f)/20.0f))) + (tarCamSpd50 * ((curActorSpd-30.0f)/20.0f));
                }
                else if (curActorSpd < 70.0f)
                {
                    tarCamLoc = (tarCamSpd50 * (1 - ((curActorSpd-50.0f)/20.0f))) + (tarCamSpd70 * ((curActorSpd-50.0f)/20.0f));
                }
                else
                {
                    tarCamLoc = tarCamSpdH;
                }

                float rate = 0.1f;  //rate of camera view change
                float slowrate = 0.1f;  //rate of camera view change
                //float slowrate = 0.3f;  //rate of camera view change

                float tarStretch = 1.0f;
                //Change View based on speed
               if (curActorSpd > 33.0f)
                {
                    //xStretch = 50.0f / curActorSpd;
                    //xStretch = (33.0f / curActorSpd) * (1/10.0f);
                    tarStretch = (curActorSpd / 33.0f);
                }

               //You get about 3.0 stretch at around 1000, so lets double the effect at this speed XD
               if (tarStretch > 3.0f)
               {tarStretch = tarStretch * (1.0f + ((tarStretch - 3.0f) * 3.0f));rate = 0.5f;}



               //Smooth rate of change by linear amount
               //xStretch = ((xStretch * 0.75f) + (tarStretch * 0.25f));
               
               //printf("tarStretch: %f\n", tarStretch);

                //printf("xStretch1: %f\n", xStretch);
                if (xStretch < (tarStretch-rate))
                {xStretch = xStretch + rate;}
                else if (xStretch > (tarStretch+slowrate))
                {xStretch = xStretch - slowrate;}
                else
                {xStretch = tarStretch;}
                //printf("xStretch2: %f\n", xStretch);





                //set look at in local space
                NxVec3 tarCamLookAt = NxVec3(targetDistance / 3,(disAbove * 3 / 4),0.0f);

                //Transform to car's location
                tarCamLoc = targetActor->getGlobalPose() * tarCamLoc;
                tarCamLookAt = targetActor->getGlobalPose() * tarCamLookAt;



                //calculate a vector to tarCamLoc
                NxVec3 vecCamLoc = tarCamLoc - curCamLoc;



                //Spring
                float mass = 50.0f;
                float stiffness = 2000.0f;
                float damping = 30.0f;
                NxVec3 stretch = (curCamLoc - tarCamLoc);//position - desiredPosition;
                NxVec3 force = (-stiffness * stretch) - (damping * vecCamLoc);

                //f=ma
                //apply force to vecCamLoc
                vecCamLoc = vecCamLoc * (force.magnitude()/10000.0f);







                //calculate a vector to tarCamLookAt
                NxVec3 vecCamLookAt = tarCamLookAt - curCamLookAt;


                //Spring for LookAt
                float mass2 = 50.0f;
                float stiffness2 = 100.0f;
                float damping2 = 600.0f;
                NxVec3 stretch2 = (curCamLookAt - tarCamLookAt);//position - desiredPosition;
                NxVec3 force2 = (-stiffness2 * stretch2) - (damping2 * vecCamLookAt);

                //f=ma
                //apply force to vecCamLoc
                vecCamLookAt = vecCamLookAt * (force2.magnitude()/10000.0f);






                //Adds rumble
                float ratio = 0.06111111f;
                vecCamLoc *= ratio;
                //vecCamLoc = vecCamLoc * vecCamLoc.magnitude();
                float magVecCamLoc = vecCamLoc.magnitude();
                //if (magVecCamLoc < 1.0f){vecCamLoc = vecCamLoc * 0.11111f;}

                //printf("curCamVec %f %f %f\n", vecCamLoc.x, vecCamLoc.y, vecCamLoc.z);

//                if (lastCamLoc != NULL)
//                {vecCamLoc = ((lastCamLoc * 0.9) + (vecCamLoc * 0.1));}

                curCamLoc = curCamLoc + (vecCamLoc);
                //curCamLoc = (curCamLoc * 0.5f) + (tarCamLoc * 0.5f);

                //curCamLoc = curCamLoc + targetActor->getLinearVelocity() ;


                curCamLookAt = curCamLookAt + (vecCamLookAt);
                //curCamLookAt = (curCamLookAt * 0.5f) + (tarCamLookAt * 0.5f);
                //curCamLookAt = curCamLookAt + (vecCamLookAt * 0.5f);
                //curCamLookAt = tarCamLookAt;

                //test to smooth
                //lastCamLoc = vecCamLoc;
                
 //               curCamLoc = tarCamLoc;
 //               curCamLookAt = tarCamLookAt;

                if (userCamControl.magnitude() > 0.2f)
                {
                    NxVec3 newCam = targetActor->getGlobalPose() * (NxVec3(userCamControl.x * 10.0f,3.5f,-userCamControl.z * 10.0f));
                    curCamLoc = newCam;
                }
                break;
            }


   case 5:
       {
                //Set target camera location in local space
                float disAbove = 5.0f;
                NxVec3 tarCamLoc = NxVec3(-targetDistance,disAbove,0.0f);

                //set look at in local space
                NxVec3 tarCamLookAt = NxVec3(targetDistance / 3,(disAbove * 3 / 4),0.0f);

                //Transform to car's location
                tarCamLoc = targetActor->getGlobalPose() * tarCamLoc;
                tarCamLookAt = targetActor->getGlobalPose() * tarCamLookAt;

           //curOrientation;

           //calculate target

           //project camera to gyro cam location
                NxVec3 gyroCam = (curCamLoc - targetActor->getGlobalPose().t);
                gyroCam = gyroCam / gyroCam.normalize();

           //move cam towards target
                gyroCam = (gyroCam + tarCamLoc) / 2;

                curCamLoc = gyroCam;

       }

   }//EndSwitch

          



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
