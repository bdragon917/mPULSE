#include <Util/Profile.h>

Profile::Profile()
{
    data.driverName = "";
    data.carModel = 1;
    data.carTexture = 3;
    data.Obs = 0;
    data.isAI = 0;

    data.shuntingLevel = 0;
    data.batteryLevel = 0;
    data.maxSpeed = 0;
    data.missileLevel = 0;
    data.barrierLevel = 0;
    data.shieldLevel = 0;

    data.style.smoothness = 0;
    data.style.wildness = 0;
    data.style.accuracy = 0;
    data.style.pickupBehavior = 0;
    data.style.steeringBehavior = 0;
}

void Profile::addData(std::vector<std::string>* newData)
{
    if(newData->size() > 1)
    {
        if(newData->at(0).compare("driveName") == 0)
            data.driverName = newData->at(1);
        else if(newData->at(0).compare("carModel") == 0)
            data.carModel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("carTexture") == 0)
            data.carTexture = atoi(newData->at(1).data());
        else if(newData->at(0).compare("Obs") == 0)
            data.Obs = atoi(newData->at(1).data());
        else if(newData->at(0).compare("isAI") == 0)
            data.isAI = atoi(newData->at(1).data());
        else if(newData->at(0).compare("shuntingLevel") == 0)
            data.shuntingLevel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("batteryLevel") == 0)
            data.batteryLevel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("maxSpeed") == 0)
            data.maxSpeed = atoi(newData->at(1).data());
        else if(newData->at(0).compare("missileLevel") == 0)
            data.missileLevel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("barrierLevel") == 0)
            data.barrierLevel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("shieldLevel") == 0)
            data.shieldLevel = atoi(newData->at(1).data());
        else if(newData->at(0).compare("smoothness") == 0)
            data.style.smoothness = atoi(newData->at(1).data());
        else if(newData->at(0).compare("wildness") == 0)
            data.style.wildness = atoi(newData->at(1).data());
        else if(newData->at(0).compare("accuracy") == 0)
            data.style.accuracy = atoi(newData->at(1).data());
        else if(newData->at(0).compare("pickupBehavior") == 0)
            data.style.pickupBehavior = atoi(newData->at(1).data());
        else if(newData->at(0).compare("steeringBehavior") == 0)
            data.style.steeringBehavior = atoi(newData->at(1).data());
    }
    
}