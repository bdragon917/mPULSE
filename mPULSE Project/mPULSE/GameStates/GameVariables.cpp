#include <GameStates/GameVariables.h>

GameVariables* GameVariables::getInstance()
{
	static GameVariables gameVariables;
	return &gameVariables;
}

void GameVariables::initialize()
{
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
}

int GameVariables::addPlayer(int controllerIndex)
{
    if (players.size() < 2)             //Limit on player number
    {
        Profile* defaultProfile = new Profile();
        defaultProfile->driverName = "Player2";
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
        defaultProfile->driverName = "Player2";
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
