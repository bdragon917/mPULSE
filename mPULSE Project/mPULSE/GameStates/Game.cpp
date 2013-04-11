#include <GameStates/Game.h>

Game::Game()
{
    state = InitState::getInstance();
    gameClock = new Clock(60.0f);
    quit = false;
}
void Game::update()
{       
    checkStateChange(); //This method checks if Game should change state and preforms a state change if needed
    state->update(gameClock->getDeltaTime());      
}

void Game::render()
{
    state->render();
    quit = state->quit; //Check if game should quit
}

bool Game::handleKeyboardMouseEvents(SDL_Event& KeyboardMouseEvents)
{
    if((KeyboardMouseEvents.type == SDL_QUIT) || state->quit)
        return false;

	return state->handleKeyboardMouseEvents(KeyboardMouseEvents);
}

void Game::handleXboxEvents(int player,XboxController* controller)
{
	state->handleXboxEvents(player, controller);    
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
        case GameState::INIT:
            state = InitState::getInstance();                
            break;
        case GameState::MAIN_MENU:
            state = MainMenuState::getInstance();                
            break;
        case GameState::STORY:
            state = StoryState::getInstance();
            break;
        case GameState::SETTING:
            state = SettingState::getInstance();
            break;
        case GameState::SHOP:
            state = ShopState::getInstance();
            break;
        case GameState::PROFILE:
            state = ProfileState::getInstance();                
            break;   
        case GameState::PLAY:
            state = PlayState::getInstance();                
            break;
        case GameState::RESULT:
            state = ResultState::getInstance();                
            break;
        case GameState::STAGE:
            state = StageSelectState::getInstance();                
            break;
        }
    }
}
    