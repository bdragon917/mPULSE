#include <Util/AI_Names.h>

AI_Names::AI_Names(void)
{
    angryName.push_back("Angercraze");
    angryName.push_back("Mr. Pain");
    angryName.push_back("Sullivan");


    randomName.push_back("Mark Kolzar");
    randomName.push_back("Ken");
    randomName.push_back("Jesse");
    randomName.push_back("Brown");
    randomName.push_back("Guy");
    randomName.push_back("Samua");
    randomName.push_back("Jake");

    curAngryName = 0;
    curRandomName = 0;
    printf("AI now can be named Initialized\n");
}

std::string AI_Names::getAngryName()
{
    if (curAngryName < angryName.size()-1)
    {
        curAngryName++;
        return angryName[curAngryName];
    }
    else
    {
        return "some Angry Guy";
    }
}


std::string AI_Names::getRandomName()
{
    if (curRandomName < randomName.size()-1)
    {
        curRandomName++;
        return randomName[curRandomName];
    }
    else
    {
        return "some Random Guy";
    }
}

AI_Names* AI_Names::getInstance()
{
	static AI_Names aI_Names;
	return &aI_Names;
}