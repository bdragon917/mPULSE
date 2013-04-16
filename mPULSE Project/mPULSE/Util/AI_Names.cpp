#include <Util/AI_Names.h>

AI_Names::AI_Names(void)
{
    angryName.push_back("Angercraze");
    angryName.push_back("Mr. Pain");
    angryName.push_back("The Mad Bull");
    angryName.push_back("Gi Hub'ra DeLoada");
    angryName.push_back("ODC 585");
    angryName.push_back("ODC 586");

    randomName.push_back("Mark Kolzar");
    randomName.push_back("Ken");
    randomName.push_back("Jesse");
    randomName.push_back("Jake Gorb");
    randomName.push_back("Claire Nightingale");
    randomName.push_back("Inari Kuna");
    randomName.push_back("C. Shepard");
    randomName.push_back("Tonoe Nusf");
    randomName.push_back("Bastila Shan");
    randomName.push_back("Cynthia");
    randomName.push_back("Ruernn Gihh");
    randomName.push_back("TT Goona");
    randomName.push_back("T.F.C. Journey");
    randomName.push_back("P. Domino");

    curAngryName = 0;
    curRandomName = 0;

    int angryPPLSeed = (rand() % 20) + 1;
    int randPPLSeed = (rand() % 20) + 1;

    printf("AI now can be named Initialized\n");
}

std::string AI_Names::getAngryName()
{
    std::string retVal;

        //Using a custom hash function to randomize names
        int getIndex = ((curAngryName + 1) * angryPPLSeed * angryPPLSeed) % angryName.size();
        curAngryName++;

        if (curAngryName >= angryName.size())
        {
            curAngryName = 0;
            angryPPLSeed = (rand() % 20) + 1;
        }

    //retVal = angryName[getIndex];
        retVal = angryName[getIndex];

    return retVal; 

}


std::string AI_Names::getRandomName()
{
    std::string retVal;

    if (randPPLSeed == 0)
        randPPLSeed = (rand() % 20) + 1;

    //Using a custom hash function to randomize names
    int getIndex = ((curRandomName + 1) * randPPLSeed * randPPLSeed) % randomName.size();


    curRandomName ++;

    if (curRandomName >= randomName.size())
    {
        curRandomName = 0;
        randPPLSeed = (rand() % 20) + 1;
    }
    
    const char* aVal = randomName[getIndex].c_str();
    //retVal = randomName[getIndex];
    retVal = randomName[getIndex];
    
    printf(aVal);
    return retVal;
}

AI_Names* AI_Names::getInstance()
{
	static AI_Names aI_Names;
	return &aI_Names;
}