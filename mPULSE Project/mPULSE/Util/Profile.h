#pragma once
#include <stdio.h>

#include <iostream>


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