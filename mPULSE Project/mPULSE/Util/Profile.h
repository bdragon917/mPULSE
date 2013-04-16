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
		int batteryLevel;
		int strafeLevel;
        int missileLevel;
        int barrierLevel;
        int shieldLevel;
        int boostLevel;
        drivingStyle style;

        int isAI;

		int shipsOwned[5];
    };

    Profile();

    Profile(std::string aName);

    void addData(profileData newData);
    void addData(std::vector<std::string>* newData);    
    profileData data;

};