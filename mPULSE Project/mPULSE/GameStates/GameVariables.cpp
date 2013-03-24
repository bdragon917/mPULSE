#include <GameStates/GameVariables.h>

GameVariables* GameVariables::getInstance()
{
	static GameVariables gameVariables;
	return &gameVariables;
}

void GameVariables::initialize()
{
    loadAllProfiles(".\\Util\\profiles.txt");
    if (players.size() == 0)             //Initalize if there is no players already loaded  //Might wanna do auto
    {
        controllers = new bool[4];
        controllers[0] = true;
        controllers[1] = false;
        controllers[2] = false;
        controllers[3] = false;
        
        numPlayers = 1;
        Profile* defaultProfile = new Profile();
        players.push_back(defaultProfile);

        player2isAI = false;
        profileTargetPlayer = 1;
        
        finishTime = NULL;
    }
    numberOfAIs = 6;
    loadedTracks = new Tracks("tracks.txt");
}

int GameVariables::addPlayer(int controllerIndex)
{
    if (players.size() < 2)             //Limit on player number
    {
        Profile* defaultProfile = new Profile();
        defaultProfile->data.driverName = "Player2";
        players.push_back(defaultProfile);
        numPlayers++;
        controllers[controllerIndex] = true;
        return (players.size() - 1);    //return player index
    }
    else
    {printf("Hey! Too many human players! (GameVariables::addPlayers)\n");return -1;}                        //return -1 if too many players
}

void GameVariables::setControllers(bool* controllerArray)
{
    controllers = controllerArray;
}

bool* GameVariables::getControllers()
{
    return controllers;
}

void GameVariables::removePlayer(int controllerIndex)
{
    if(controllerIndex < 4)
    {
        players[controllerIndex] = false;
        numPlayers--;
    }
}

int GameVariables::addPlayers(Profile* aPlayer)
{
    if (players.size() < 2)             //Limit on player number
    {
        players.push_back(aPlayer);
        return (players.size() - 1);    //return player index
    }
    else
    {printf("Hey! Too many human players! (GameVariables::addPlayers)\n");return -1;}                        //return -1 if too many players
}

int GameVariables::addPlayerTwo()
{
    if (players.size() < 2)             //Limit on player number
    {
        Profile* defaultProfile = new Profile();
        defaultProfile->data.driverName = "Player2";
        players.push_back(defaultProfile);
        numPlayers++;
        controllers[1] = true;
        return (players.size() - 1);    //return player index
    }
    else
    {printf("Hey! Too many human players! (GameVariables::addPlayers)\n");return -1;}                        //return -1 if too many players
}

int GameVariables::setPlayers(Profile* aPlayer, int index)
{
    players.at(index) = aPlayer;    //possibly save the old profile???
    return 0;
}

int GameVariables::getPlayerNum()
{
    return players.size();
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

    for (unsigned int p=0;p<players.size();p++)
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
            substrings->push_back(line.substr(lastDelimiterSeen,lastDelimiterSeen+i));
            lastDelimiterSeen = i;
        }
    }
    if(lastDelimiterSeen == 0)
        substrings->push_back(line.substr(lastDelimiterSeen));
    else 
        substrings->push_back(line.substr(lastDelimiterSeen+1));

    return substrings;
}

void GameVariables::finalizeProfiles()
{
    profiles.shrink_to_fit();
}
