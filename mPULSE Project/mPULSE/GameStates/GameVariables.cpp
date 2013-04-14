#include <GameStates/GameVariables.h>

GameVariables* GameVariables::getInstance()
{
	static GameVariables gameVariables;
	return &gameVariables;
}


void GameVariables::initialize()
{
    loadAllProfiles(".\\Util\\profiles.txt");
	players.push_back(new Profile());
	players.push_back(new Profile());

	finishTime = NULL;
    numLaps = 3;
    numberOfAIs = 6;
    selectedTrack = 0;
    loadedTracks = new Tracks("tracks.txt");
    isLoaded = false;
}

void GameVariables::setControllers(bool* controllerArray)
{
    controllers = controllerArray;
}

bool* GameVariables::getControllers()
{
    return controllers;
}

void GameVariables::setPlayerProfile(Profile* aPlayer, unsigned index)
{
    if (players.size() >= index)
        players.at(index-1) = aPlayer;    //possibly save the old profile???
    else
    {MessageBox(NULL, "GameVariables: ERROR: Players <array> isn't big enough, cannot set.", NULL, NULL);}
}

Profile* GameVariables::getPlayerProfile(int player)
{
	return players.at(player);
}

void GameVariables::setNumPlayers(int num)
{
	numPlayers = num;
}

int GameVariables::getNumPlayers()
{
	return numPlayers;
}

void GameVariables::setProfileCurrentPlayer(int num)
{
	profileCurrentPlayer = num;
}

int GameVariables::getProfileCurrentPlayer()
{
	return profileCurrentPlayer;
}

void GameVariables::resetRace()
{
    finishedPlayers[0] = false;
    finishedPlayers[1] = false;
    finishedPlayers[2] = false;
    finishedPlayers[3] = false;

}

bool GameVariables::isFinishedRace()
{
    bool retValue = true;

    for (int p=0;p<numPlayers;p++)
    {
        if (!finishedPlayers[p])
            retValue = false;
    }

    return retValue;
}

void GameVariables::becomeFinished(int player)
{
    finishedPlayers[player] = true;
}

bool GameVariables::isFinished(int player)
{
    return finishedPlayers[player];
}

void GameVariables::loadAllProfiles(std::string filename)
{      
    char charArray[1024];
    std::string tmpLine = "";
    Profile* profile;
    std::vector<std::string>* substrings;
    std::ifstream file;
    bool profileSeen = false;

	file.open(filename);	
    if(file.is_open())
    {
	    while(!file.eof())
	    {
            //Read a line
            file.getline(charArray,1024);
            tmpLine = charArray;

            //Check if the line is empty or a comment
            if(tmpLine.size() <= 0 || tmpLine.at(0) == '/')
                continue;
            
            if(profileSeen)
            {
                if (tmpLine.at(0) == '#')
                {
                    profiles.push_back(profile);
                    profileSeen = false;
                }
                else
                {
                    substrings = split(tmpLine,'|');
                    profile->addData(substrings);
                }
            }
            else if(tmpLine.at(0) == '#')
            {
                profileSeen = true;
                profile = new Profile;
            }
        }
        file.close();                
    }
    else
        printf("Track checkpoints didn't open, can't find maybe??\n");	    
    finalizeProfiles();
}

std::vector<std::string>* GameVariables::split(std::string line, char delimiter)
{
    std::vector<std::string>* substrings = new std::vector<std::string>;

    unsigned lineLength = line.size();
    unsigned lastDelimiterSeen = 0;

    for(unsigned i=0;i<lineLength;i++)
    {
        if(line.at(i) == delimiter)
        {

            std::string sub = line.substr(lastDelimiterSeen,lastDelimiterSeen + i);
            std::string sub2 = line.substr(lastDelimiterSeen,i-lastDelimiterSeen);
            substrings->push_back(line.substr(lastDelimiterSeen,i-lastDelimiterSeen));
            lastDelimiterSeen = i + 1;
        }
    }
    if(lastDelimiterSeen == 0)
        substrings->push_back(line.substr(lastDelimiterSeen));
    else 
        substrings->push_back(line.substr(lastDelimiterSeen));

    return substrings;
}

void GameVariables::finalizeProfiles()
{
    profiles.shrink_to_fit();
}
