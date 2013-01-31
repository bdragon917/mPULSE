#include "Game.h"

    Game::Game()
    {
        state = InitState::getInstance();
    }
    void Game::update(float dt)
    {       
       checkStateChange();
       state->update(dt);
    }

    void Game::render()
    {
        state->render();
    }

    bool Game::handleKeyboardMouseEvents(SDL_Event& KeyboardMouseEvents)
    {
        if(KeyboardMouseEvents.type == SDL_QUIT)
            return false;

        state->handleKeyboardMouseEvents(KeyboardMouseEvents);
        return true;
    }

    void Game::handleXboxEvents(int player,XINPUT_STATE* state)
    {

    }

    void Game::checkStateChange()
    {
        GameState::StateType tmpType = state->pollStateChange();

        if(stateType != tmpType)
        {
            stateType = tmpType;
            switch(stateType)
            {
            case GameState::StateType::INIT:
                state = InitState::getInstance();
                state->changeStateType(GameState::StateType::INIT);
                break;
            case GameState::StateType::PLAY:
                state = PlayState::getInstance();
                state->changeStateType(GameState::StateType::PLAY);
                break;
            }
        }
    }
//
///*
//*Game: This method runs the game, returns false if the game should quit and true otherwise. 
//*/
//bool Game::run()
//{   
//    switch(state)
//    {
//        case 
//
//    }
//    InputController inController;
//    inController.updateController();
//
//	SDL_Event event;
//    Clock clock(60);
//    Game game();
//    return true;
//}
//
//
//bool init()
//{
//    SDL_Surface* inImg = NULL;		//Used to load the image into the memory
//    SDL_Surface* Optimized = NULL;	//Used to change the format to the native display format for faster display
//    SDL_Surface* screen = NULL;
//
//    numPlayers = 0;
//    currentPackNum = 0;
//    gameRunning = true;   
//    XboxController* players[MAX_PLAYERS];
