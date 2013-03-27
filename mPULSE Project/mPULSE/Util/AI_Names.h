#include <string>
#include <vector>

#pragma once
class AI_Names
{
public:
	static AI_Names* getInstance();

    std::string getName(int Type);
    std::string getAngryName();
    std::string getRandomName();

private:
	AI_Names();


    std::vector<std::string> angryName;
    std::vector<std::string> randomName;
    unsigned curAngryName;
    unsigned curRandomName;
};