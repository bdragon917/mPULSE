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

        NxVec3 myDirection = NxVec3(0.0f, 0.0f, 1.0f);
        myDirection = myActor->getGlobalOrientation() * myDirection;
        myOrientation = myDirection;
        //myDirection = myDirection / myDirection.normalize();

        NxVec3 myTarget = targetWaypoint->pos;
        myTarget = myTarget - myActor->getGlobalPose().t;
        //myTarget = myTarget / myTarget.normalize();

        myTargetVector = myTarget;      //for debug

        float angleToTarget = myDirection.dot(myTarget);

        printf("AI: AngleToTarget%f\n", angleToTarget);

        if (angleToTarget > 0)
        {
            printf("AI: Steering right\n");
            //steer right
            myTarget.normalize();
            xController->leftStick.x = myTarget.x;
            xController->leftStick.y = myTarget.z;
            xController->leftStick.magnitude = angleToTarget * 10000;

            xController->rTrigger = 255;

        }
        else
        {
            //steer left
            printf("AI: Steering left\n");
            myTarget.normalize();
            xController->leftStick.x = myTarget.x;
            xController->leftStick.y = myTarget.z;
            xController->leftStick.magnitude = angleToTarget * 10000;

            xController->rTrigger = 255;

        }
    //if (myActor->getGlobalOrientation
    
    
    
    
    }

    void AI::setActor(NxActor* aA)
    {
        myActor = aA;
    }

    void AI::setWaypoint(Waypoint* aW)
    {
        targetWaypoint = aW;
    }