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
        Profile* defaultProfile = new Profile();
        players.push_back(defaultProfile);
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
