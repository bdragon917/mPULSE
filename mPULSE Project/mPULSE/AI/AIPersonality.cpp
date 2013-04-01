#include <AI/AIPersonality.h>

AIPersonality::AIPersonality()
{

    Boidness = 1.0f;     //used
    PlayerHate = 0.1f;   //Used

    lookAhead = 20.0f;
    lookRadius = 50.0f;

    AHFactor = 0.0f;         //Steer in front of you
    Safeness = 0.0f;         //Avoidance tendecy
    Jerk = 0.0f;             //Chance of Jerk moves
    Cool = 0.0f;             //Focus
}


void AIPersonality::setPersonality(int index)
{
    switch (index)
    {
        case 0:     //CheckpointFollower
        {
            Boidness = 0.0f;     //used
            PlayerHate = 0.0f;   //Used
            break;
        }


        case 1:     //Weak
        {
            Boidness = 1.0f;     //used
            PlayerHate = -0.1f;   //Used
            break;
        }


        case 2:     //Aggressive
        {
            lookAhead = -37.0f;     //wierd, is this opposite
            lookRadius = 40.0f;
            Boidness = 0.0f;     //used
            PlayerHate = 1.0f;   //Used
            break;
        }

        case 3:     //Chump?
        {
            Boidness = 0.5f;     //used
            PlayerHate = 0.5f;   //Used
            break;
        }


    }
}
