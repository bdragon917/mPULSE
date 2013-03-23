#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class Tracks
{
public:   
    Tracks(std::string trackInfo);

    int getNumberofTracks();
    std::string getTrackFilename(int i);

private:
    void loadFromFile(std::string filename);
    std::vector<std::string> filenames;


    
};

