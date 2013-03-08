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

    typedef enum {
        STANDARD,
        LAPTOP,
        GAMELAB,
        FULLSCREEN
    } Resolution;

    Resolution curResolution;

private:
    std::vector<Profile*> players; 
    int numPlayers;
    bool* controllers;
};