#include <AI/AIPersonality.h>

AIPersonality::AIPersonality()
{
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

            break;
        }


        case 1:     //Weak
        {

            break;
        }


        case 2:     //Aggressive
        {

            break;
        }




    }
}
