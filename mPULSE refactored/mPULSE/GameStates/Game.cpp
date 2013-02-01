#include "Game.h"

    Game::Game()
    {
        state = InitState::getInstance();
    }
    void Game::update(float dt)
    {       
       checkStateChange(); //This method checks if Game should change state and preforms a state change if needed
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
        //Check if the state should be changed
        GameState::StateType tmpType = state->pollStateChange();

        if(stateType != tmpType)
        {
            //Change the state
            stateType = tmpType;
            switch(stateType)
            {
            case GameState::StateType::INIT:
                state = InitState::getInstance();                
                break;
            case GameState::StateType::PLAY:
                state = PlayState::getInstance();                
                break;
            }
        }
    }