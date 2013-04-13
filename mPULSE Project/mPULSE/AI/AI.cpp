//Find angle between two vectors
/*
float xz = x*x + z*z, y11 = y1*y1, y12 = y1*y2, y22 = y2*y2;

float cosangle = (xz + y12) / sqrt((xz + y11) * (xz + y22));
float angle = acos(cosangle);
*/

#include <AI/AI.h>
#include <iostream>

AI::AI()
{
    xController = new XboxController(5);myTargetVector = NxVec3(0,0,0);myOrientation = NxVec3(0,0,0);myPersonality = AIPersonality();
}

XboxController* AI::getControl()
{
    return xController;
}

void AI::setPersonality(int type)
{
    myPersonality.setPersonality(type);
}



void AI::update(std::vector<Entity*> players, std::vector<Entity*> AIs)
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
    
    //myTarget = myTarget / myTarget.normalize();


   myTarget = (myPersonality.Boidness * addBoydFlocking(myTarget, AIs, players)) + ((1 - myPersonality.Boidness) * myTarget);
   myTarget = (myPersonality.PlayerHate * attackPlayerInRange(myTarget, players)) + ((1 - myPersonality.PlayerHate) * myTarget);
   playSounds();

        /*
    myTarget = addBoydFlocking(myTarget, AIs, players);
    myTarget = attackPlayerInRange(myTarget, players);
    */

    myTargetVector = myTarget;      //myTargetVector for debug

    myTarget.normalize();

    //applySpeedBoost(AIs);


    //myTargetVector = myTarget;      //myTargetVector for debug

    //float angleToTarget = myDirection.dot(myTarget);
    float angleToTarget = myTarget.dot(myDirection);
    //float angleToTarget = (myDirection.x * myTarget.y) - (myDirection.x * myTarget.y);

    //std::cout << "AI: AngleToTarget" << angleToTarget << std::endl;

    //angleToTarget = acos((angleToTarget) / (myDirection.magnitude() * myTarget.magnitude()));
    //angleToTarget = acos((angleToTarget)/(myTarget.magnitude()*myDirection.magnitude()));
    //printf("AI: AngleToTarget%f\n", angleToTarget);
    // -1.0 < AngleTotarget < 1.0 

    float SteerSenstivity = 0.03f;

    if (angleToTarget > SteerSenstivity)
    {
        //steer right
        myTarget.normalize();

        //Steering
        xController->leftStick.x = 1;

        //finalize Steering
        if (xController->leftStick.x > 1.0f)
            xController->leftStick.x = 1.0f;
        else if (xController->leftStick.x < -1.0f)
            xController->leftStick.x = -1.0f;
        //xController->leftStick.y = myTarget.z;
        //xController->leftStick.magnitude = angleToTarget * 24000;
        xController->leftStick.magnitude = 24000 * (((angleToTarget) / 2) + 0.5f);

        //This will change the amount of accelerate depending on angle steer
        //1.0 > angleToTarget > 0.03
        if (angleToTarget < 0.25f)
            xController->rTrigger = 175;
        else if (angleToTarget < 0.5f)
            xController->rTrigger = 135;
        else if (angleToTarget < 0.75f)
            xController->rTrigger = 75;
        else
            xController->rTrigger = 35;
        

    }
    else if (angleToTarget < -SteerSenstivity)
    {
        //steer left
        myTarget.normalize();

        //steering
        xController->leftStick.x = -1;

        //finalize Steering
        if (xController->leftStick.x > 1.0f)
            xController->leftStick.x = 1.0f;
        else if (xController->leftStick.x < -1.0f)
            xController->leftStick.x = -1.0f;
        //xController->leftStick.y = myTarget.z;
        //xController->leftStick.magnitude = angleToTarget * 24000;
        xController->leftStick.magnitude = 24000 * (((-angleToTarget) / 2) + 0.5f);

        //This will change the amount of accelerate depending on angle steer
        //-1.0 > angleToTarget > -0.03
        if (angleToTarget > -0.25f)
            //xController->rTrigger = 175;
            xController->rTrigger = 6;
        else if (angleToTarget > -0.5f)
            //xController->rTrigger = 135;
            xController->rTrigger = 5;
        else if (angleToTarget > -0.75f)
            //xController->rTrigger = 75;
            xController->rTrigger = 4;
        else
            //xController->rTrigger = 35;
            xController->rTrigger = 3;

    }
    else
    {
        //printf("AI: Driving Stright\n");
        myTarget.normalize();
        //xController->leftStick.x = myTarget.x;
        //xController->leftStick.x = xController->leftStick.x + (angleToTarget / 5);
        xController->leftStick.x = 0;
        //xController->rTrigger = 255;
        xController->rTrigger = 8;        //Weaken AI

        if (xController->leftStick.y < 0)   //If y is negative, probably due to ai logic /slow down
        {
            xController->rTrigger = (int) (xController->rTrigger - ((xController->leftStick.y + 1) * 10));    //slight decelertion
        }
    }
//if (myActor->getGlobalOrientation
    
}


void AI::playSounds()
{
    /*
    CustomData* cs = (CustomData*) myActor->userData;

    Entity* aEntity = cs->entity;

    NxWheelContactData nxwcd; 
    aEntity->getDriveWheels()->at(0)->getContact(nxwcd); //get contact data

    if ( aEntity->getDriveWheels()->at(0)->getContact(nxwcd) == NULL)
    {
        SoundEngine* soundEngine = SoundEngine::getInstance();
        soundEngine->playSound(3,12);    //3 is channel, 7 is index for MenuPress
    }
    */
}

NxVec3 AI::attackPlayerInRange(NxVec3 myTarget, std::vector<Entity*> players)
{
    NxVec3 retValue = myTarget;

    float viewDistance = myPersonality.lookRadius;
    float lookAheadDistance = myPersonality.lookAhead;


    NxVec3 myLoc = myActor->getGlobalPose().t;
    NxVec3 LookAtLoc = myActor->getGlobalPose() * NxVec3(0.0f, 0.0f, lookAheadDistance );

    //Look at Players
    
    for (unsigned int i=0;i<players.size();i++)
    {
        NxVec3 otherLoc = players[i]->getActor()->getGlobalPose().t;

        //Set to player if in range
        if (LookAtLoc.distance(otherLoc) < viewDistance)
        {
            //And is closest
            if (LookAtLoc.distance(otherLoc) < LookAtLoc.distance(retValue))
            {
                retValue = otherLoc;
                retValue = retValue - myLoc;
            }
        }

    }
    

    return retValue;
}


NxVec3 AI::addBoydFlocking(NxVec3 curTargetVector, std::vector<Entity*> AIs, std::vector<Entity*> players)
{
    float viewDistance = myPersonality.lookRadius;
    const float seperateIntensity = 1.0f;
    float lookAheadDistance = myPersonality.lookAhead;
    const float BoydAmount = 0.5f;      //within 0 to 1

   

    //Lets try to look more ahead if going faster
    //If (
        lookAheadDistance =+ (myActor->getLinearVelocity().magnitude() / 10.0f);
        viewDistance =+ (myActor->getLinearVelocity().magnitude() / 20.0f);




    NxVec3 retVector = curTargetVector;
    NxVec3 myLoc = myActor->getGlobalPose().t;
    NxVec3 LookAtLoc = myActor->getGlobalPose() * NxVec3(0.0f, 0.0f, lookAheadDistance );

    


    NxVec3 acumVector = NxVec3(0.0f,0.0f,0.0f);

    //Look at AI's
    for (unsigned int i=0;i<AIs.size();i++)
    {
        NxVec3 otherLoc = AIs[i]->getActor()->getGlobalPose().t;

        //Boid Separation
        //Currently, this calculate distance from a circle, thats ahead by lookAheadDistance
        if (LookAtLoc.distance(otherLoc) < viewDistance)
        {
            NxVec3 vectorAway = (myLoc - otherLoc);
            acumVector = acumVector - vectorAway;
        }

    }

    //Look at Players
    for (unsigned int i=0;i<players.size();i++)
    {
        NxVec3 otherLoc = players[i]->getActor()->getGlobalPose().t;

        //Boid Separation
        //Currently, this calculate distance from a circle, thats ahead by lookAheadDistance
        if (LookAtLoc.distance(otherLoc) < viewDistance)
        {
            NxVec3 vectorAway = (myLoc - otherLoc);
            acumVector = acumVector - vectorAway;
        }

    }


    //Type1

    acumVector = acumVector * seperateIntensity;



    //retVector = ((1.0f-BoydAmount) * retVector) + ( (BoydAmount) *acumVector);

    //Type 2a
    return (retVector);
    //return (retVector - acumVector);

    //Type 2b
    //return (retVector + acumVector);

    //type 3
    //if (acumVector.x > 0)
    //{myActor->addLocalForce(NxVec3(1000.0f, 0, 0));}
    //else if (acumVector.x < 0)
    //    {myActor->addLocalForce(NxVec3(-1000.0f, 0, 0));}
    //return retVector;
}

//Not complete
//Applies speed boost if behind =)
//Currently only works linearly tho...
void AI::applySpeedBoost(std::vector<Entity*> AIs)
{
    NxVec3 myLoc = myActor->getGlobalPose().t;

    NxVec3 genLoc = NxVec3(0.0f,0.0f,0.0f);
 
    for (unsigned int i=0;i<AIs.size();i++)
    {
        NxVec3 otherLoc = AIs[i]->getActor()->getGlobalPose().t;

        genLoc = genLoc + otherLoc;
    }
    genLoc = genLoc / (NxReal) AIs.size();


    if (myLoc.distance(genLoc) > 90)
    {
        //Cheat =)
        //more gravity?
        myActor->addForce(NxVec3(0.0f, -100.0f, 0.0f));


    }

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
