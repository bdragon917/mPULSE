#pragma once

#include <string>

class Profile
{
public:
    Profile();
    Profile(char* filename);

    std::string driverName;
    int carModel;
    int carTexture;
    bool isAI;

private:

    
    //Driver name
    //Driver Car (model)
    //car stats
    //Obs
    double Obs;
};