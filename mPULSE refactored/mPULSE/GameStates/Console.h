#pragma once

#define NOMINMAX
#define NO_SDL_GLEXT

#include <stdio.h>
#include <sstream>

#include <vector>

//files
#include <iostream>
#include <stdio.h>
#include <fstream>

#include <map>

class Console
{
public:
    Console();
        //Debug output String (other functions can use this to display on screen)
        std::string debugOut;
        //Text Display (Console)
        std::string consoleString;
        std::string consoleOut[5];

        void propragateMsg(std::string feedbackMsg);
        void propragateMsg();
        void goUp();

        //void addCommand(std::string cmdStr, int(*)(int aFunc));
        //std::map<std::string, int(*)(int)> commands;
private:
        int logPointer;
        void appendExcessLog();
        void appendLog();
        std::vector<std::string> log;

        //std::map<std::string, int(*)(int)> commands;


};
