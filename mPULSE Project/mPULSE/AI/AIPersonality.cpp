#include <AI/AIPersonality.h>

AIPersonality::AIPersonality()
{

    Boidness = 1.0f;     //used
    PlayerHate = 0.1f;   //Used

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
