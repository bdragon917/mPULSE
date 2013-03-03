//Find angle between two vectors
/*
float xz = x*x + z*z, y11 = y1*y1, y12 = y1*y2, y22 = y2*y2;

float cosangle = (xz + y12) / sqrt((xz + y11) * (xz + y22));
float angle = acos(cosangle);
*/

#include "AI.h"

AI::AI(void)
{xController = new XboxController(5);myTargetVector = NxVec3(0,0,0);myOrientation = NxVec3(0,0,0);}

    AI::~AI(void)
    {}

    XboxController* AI::getControl()
    {
        return xController;
    }

    void AI::update()
    {
        xController->initializeVariables();

        NxVec3 myDirection = NxVec3(0.0f, 0.0f, 10.0f);
        myDirection = myActor->getGlobalPose() * myDirection;
        myDirection = myDirection - myActor->getGlobalPose().t;

        //myDirection = NxVec3(1.0f, 0.0f, 0.0f);
        myDirection.normalize();

        myOrientation = myDirection;
        //myDirection = myDirection / myDirection.normalize();       

        CustomData* cd = (CustomData*) myActor->userData;
        NxVec3 myTarget = cd->wp->nextWaypoint->pos;


        myTarget = myTarget - myActor->getGlobalPose().t;
        //myTarget = NxVec3(1.0f, 0.0f, 1.0f);
        myTarget.normalize();
        //myTarget = myTarget / myTarget.normalize();

        myTargetVector = myTarget;      //for debug

        //float angleToTarget = myDirection.dot(myTarget);
        float angleToTarget = myTarget.dot(myDirection);
        //float angleToTarget = (myDirection.x * myTarget.y) - (myDirection.x * myTarget.y);


        //angleToTarget = acos((angleToTarget) / (myDirection.magnitude() * myTarget.magnitude()));
        //angleToTarget = acos((angleToTarget)/(myTarget.magnitude()*myDirection.magnitude()));
        //printf("AI: AngleToTarget%f\n", angleToTarget);

        if (angleToTarget > 0.01f)
        {
           // printf("AI: Steering right\n");
            //steer right
            myTarget.normalize();
            //xController->leftStick.x = myTarget.x;
            //xController->leftStick.x = xController->leftStick.x + (angleToTarget / 5);
            xController->leftStick.x = 1;
            if (xController->leftStick.x > 1.0f)
                xController->leftStick.x = 1.0f;
            else if (xController->leftStick.x < -1.0f)
                xController->leftStick.x = -1.0f;
            //xController->leftStick.y = myTarget.z;
            //xController->leftStick.magnitude = angleToTarget * 24000;
            xController->leftStick.magnitude = 24000;

            xController->rTrigger = 75;

        }
        else if (angleToTarget < -0.01f)
        {
            //steer left
            //printf("AI: Steering left\n");
            myTarget.normalize();
            //xController->leftStick.x = myTarget.x;
            //xController->leftStick.x = xController->leftStick.x + (angleToTarget / 5);
            xController->leftStick.x = -1;
            if (xController->leftStick.x > 1.0f)
                xController->leftStick.x = 1.0f;
            else if (xController->leftStick.x < -1.0f)
                xController->leftStick.x = -1.0f;
            //xController->leftStick.y = myTarget.z;
            //xController->leftStick.magnitude = angleToTarget * 24000;
            xController->leftStick.magnitude = 24000;

            xController->rTrigger = 75;

        }
        else
        {
            printf("AI: Driving Stright\n");
            myTarget.normalize();
            //xController->leftStick.x = myTarget.x;
            //xController->leftStick.x = xController->leftStick.x + (angleToTarget / 5);
            xController->leftStick.x = 0;
            xController->rTrigger = 255;
        }
    //if (myActor->getGlobalOrientation
    
    
    
    
    }

    NxActor* AI::getActor()
    {
        return myActor;
    }

    void AI::setActor(NxActor* aA)
    {
        myActor = aA;
    }

    void AI::setWaypoint(Waypoint* aW)
    {
        targetWaypoint = aW;
    }