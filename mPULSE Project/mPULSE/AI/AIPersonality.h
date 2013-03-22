

class AIPersonality

{
public:
    AIPersonality();
    
    void setPersonality(int index);
    // 0 Checkpointer Follower
    // 1 Weak
    // 2 Aggressive
    // 3 Safe
    // 
    //

    float Boidness;     //used
    float PlayerHate;   //Used

    float AHFactor;         //Steer in front of you
    float Safeness;         //Avoidance tendecy
    float Jerk;             //Chance of Jerk moves
    float Cool;             //Focus
};


