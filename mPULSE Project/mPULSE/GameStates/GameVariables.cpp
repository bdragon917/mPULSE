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

    curResolution = LAPTOP;
	finishTime = NULL;
    numLaps = 3;
    numberOfAIs = 25;
    selectedTrack = 0;
    loadedTracks = new Tracks("tracks.txt");
    isFullScreen = false;
    isLoaded = false;
    skyboxTextureIndex.clear();
    skyboxTextureIndex.push_back(20);
    skyboxTextureIndex.push_back(21);
    skyboxTextureIndex.push_back(23);
    skyboxTextureIndex.push_back(22);
    skyboxTextureIndex.push_back(24);
    skyboxTextureIndex.push_back(25);
}

void GameVariables::addRanking(std::string rank,std::string name,std::string time)
{
    Rank ranking;
    ranking.rank = rank;
    ranking.name = name;
    ranking.time = time;
    rankings.push_back(ranking);
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


void GameVariables::saveProfiles()
{
	std::ofstream out;
    out.open( "./Util/profiles.txt" );
    if( !out )
    {
        printf( "Couldn't open file.\n");
    }
    else
    {
		for( unsigned i = 0; i < profiles.size(); i++ )
		{
			out << "#\n";
			out << "driveName|" << profiles[i]->data.driverName << "\n";
			out << "carModel|" << profiles[i]->data.carModel << "\n";
			out << "carTexture|" << profiles[i]->data.carTexture << "\n";
			out << "Obs|" << profiles[i]->data.Obs << "\n";
			out << "isAI|" << profiles[i]->data.isAI << "\n";
			out << "batteryLevel|" << profiles[i]->data.batteryLevel << "\n";
			out << "strafeLevel|" << profiles[i]->data.strafeLevel << "\n";
			out << "boostLevel|" << profiles[i]->data.boostLevel << "\n";
			out << "maxSpeed|" << profiles[i]->data.maxSpeed << "\n";
			out << "missileLevel|" << profiles[i]->data.missileLevel << "\n";
			out << "barrierLevel|" << profiles[i]->data.barrierLevel << "\n";
			out << "shieldLevel|" << profiles[i]->data.shieldLevel << "\n";
			out << "smoothness|" << profiles[i]->data.style.smoothness << "\n";
			out << "wildness|" << profiles[i]->data.style.wildness << "\n";
			out << "accuracy|" << profiles[i]->data.style.accuracy << "\n";
			out << "pickupBehavior|" << profiles[i]->data.style.pickupBehavior << "\n";
			out << "steeringBehavior|" << profiles[i]->data.style.steeringBehavior << "\n";
			out << "shipsOwned|" << profiles[i]->data.shipsOwned[0] << "|";
			out << profiles[i]->data.shipsOwned[1] << "|";
			out << profiles[i]->data.shipsOwned[2] << "|";
			out << profiles[i]->data.shipsOwned[3] << "|";
			out << profiles[i]->data.shipsOwned[4] << "\n";
			out << "#\n";
		}
    }
    out.close();
}
