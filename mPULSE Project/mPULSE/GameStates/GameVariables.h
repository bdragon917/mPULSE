#pragma once
#include <Util/Profile.h>
#include <vector>
#include <InGameObjects\Tracks.h>
#include <InGameObjects\Track.h>
#include <InGameObjects\Entities\RenderableComponent.h>
#include <RenderingEngine\DynamicImage.h>
#include <iostream>
#include <fstream>

class Track;

class GameVariables
{
public:
	static GameVariables* getInstance();
    
    void initialize();

    void loadAllProfiles(std::string filename);
    void setConnectedControllers(bool* controllerIndexes);
    bool* getConnectedControllers(bool* controllerIndexes);

    void setControllers(bool* controllerArray);
    bool* getControllers();  

	void setPlayerProfile(Profile* aPlayer, unsigned index);
	Profile* getPlayerProfile(int player);

	//Saving profiles
	void saveProfiles();

	void setNumPlayers(int num);
	int getNumPlayers();
	void setProfileCurrentPlayer(int num);
	int getProfileCurrentPlayer();

    typedef struct Rank{
        std::string rank;
        std::string name;
        std::string time;
    };

    void addRanking(std::string rank,std::string name,std::string time);

    typedef enum {
        STANDARD,
        LAPTOP,
        GAMELAB,
        LAST
    } Resolution;

    bool isFullScreen;

    Resolution curResolution;

    //determines finished race
    void resetRace();
    bool isFinishedRace();
    bool isFinished(int player);
    void becomeFinished(int player);
    unsigned int finishTime;

    int numberOfAIs;
    void finalizeProfiles();
    std::vector<std::string>* split(std::string line, char delimiter);
    std::vector<Profile*> profiles; 


    //Used by Shop State (set by Lounge state)
    Profile* playerInShop;

	//Track Stuff
    Tracks* loadedTracks;
    int selectedTrack;      //int points to PhysX Model
    bool isLoaded;
    Track* theSelectedTrack;
    float trackSelectRotVar;
    std::vector<RenderableComponent*> rcTrack;
    int minimapTextureIndex;
    int physXTrackModel;
    int musicIndex;
    int numLaps;
    int miniMapIndex;
    std::vector<RenderableComponent*> trackRC;
    std::vector<int> skyboxTextureIndex;

    std::vector<Rank> rankings;      //used to display the ranking at results

	//Transistion Variables
	std::vector<DynamicImage*> di;

private:

    //Race Variables
    bool finishedPlayers[4];        //Should be the number of players
    std::vector<Profile*> players; 

    int numPlayers;
    bool* controllers;

	//This is for profiles =)
    int profileCurrentPlayer;

};