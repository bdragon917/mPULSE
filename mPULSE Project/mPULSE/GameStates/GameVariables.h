#pragma once
#include <Util/Profile.h>
#include <vector>

class GameVariables
{
public:
	static GameVariables* getInstance();
    
    void initialize();

    int addPlayers(Profile* aPlayer);
    void setConnectedControllers(bool* controllerIndexes);
    bool* getConnectedControllers(bool* controllerIndexes);

    void setControllers(bool* controllerArray);
    bool* getControllers();

    int addPlayer(int controllerIndex);
    void removePlayer(int controllerIndex);    

    int addPlayerTwo();     //Add default profile
    int setPlayers(Profile* aPlayer, int index);

    int getPlayerNum();

    //This is for profiles =)
    int profileTargetPlayer;


    bool player2isAI;       //debug??

    typedef enum {
        STANDARD,
        LAPTOP,
        GAMELAB,
        FULLSCREEN
    } Resolution;

    Resolution curResolution;

    //determines finished race
    void GameVariables::resetRace();
    bool GameVariables::isFinishedRace();
    bool GameVariables::isFinished(int player);
    void GameVariables::becomeFinished(int player);
    unsigned int finishTime;
    //

private:

    //Race Variables
    bool finishedPlayers[4];        //Should be the number of players
    //

    std::vector<Profile*> players; 
    int numPlayers;
    bool* controllers;
};