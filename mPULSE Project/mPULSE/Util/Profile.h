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

private:
    //Driver name
    //Driver Car (model)
    //car stats
    //Obs
};