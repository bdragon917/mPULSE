#pragma once

#include <string>
#include <vector>
#include <stdlib.h>

class Profile
{
public:
    struct drivingStyle
    {
        int smoothness;
        int wildness;
        int accuracy; //ability to fall off the track
        int steeringBehavior;
        int pickupBehavior;
    };

    struct profileData
    {
   
        std::string driverName;    
        int carModel;
        int carTexture;

        int Obs;
        int maxSpeed;
        int missileLevel;
        int barrierLevel;
        int shieldLevel;
        int shuntingLevel;
        int batteryLevel;
        drivingStyle style;

        int isAI;
    };

    Profile();
    void addData(profileData newData);
    void addData(std::vector<std::string>* newData);    
    profileData data;

private:

    
    //Driver name
    //Driver Car (model)
    //car stats
    //Obs
    double Obs;
};