#pragma once
#include <Util/Profile.h>
#include <vector>

class GameVariables
{
public:
	static GameVariables* getInstance();
    
    void GameVariables::initialize();

    int addPlayers(Profile* aPlayer);
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
};