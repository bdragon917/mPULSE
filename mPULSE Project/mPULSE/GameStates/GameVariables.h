#pragma once
#include <Util/Profile.h>
#include <vector>
#include <InGameObjects\Tracks.h>
#include <InGameObjects\Track.h>
#include <InGameObjects\Entities\RenderableComponent.h>
#include <iostream>
#include <fstream>

class Track;

class GameVariables
{
public:
	static GameVariables* getInstance();
    
    void initialize();

    void loadAllProfiles(std::string filename);
    int addPlayers(Profile* aPlayer);
    void setConnectedControllers(bool* controllerIndexes);
    bool* getConnectedControllers(bool* controllerIndexes);

    void setControllers(bool* controllerArray);
    bool* getControllers();

    int addPlayer(int controllerIndex);
    void removePlayer(unsigned controllerIndex);    

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
        FULLSCREEN,
        LAST
    } Resolution;

    Resolution curResolution;

    //determines finished race
    void resetRace();
    bool isFinishedRace();
    bool isFinished(int player);
    void becomeFinished(int player);
    unsigned int finishTime;
    //

    Profile* getPlayerProfile(int player);

    int numberOfAIs;
    void finalizeProfiles();
    std::vector<std::string>* split(std::string line, char delimiter);
    std::vector<Profile*> profiles; 



    Tracks* loadedTracks;
    int selectedTrack;      //int points to PhysX Model
    Track* theSelectedTrack;
    float trackSelectRotVar;
    std::vector<RenderableComponent*> rcTrack;
    int minimapTextureIndex;
    int physXTrackModel;
    int musicIndex;
    std::vector<RenderableComponent*> trackRC;


    std::vector<std::string> rankings;      //used to display the ranking at results

private:


    //Race Variables
    bool finishedPlayers[4];        //Should be the number of players
    std::vector<Profile*> players; 
    
    int numPlayers;
    bool* controllers;
};