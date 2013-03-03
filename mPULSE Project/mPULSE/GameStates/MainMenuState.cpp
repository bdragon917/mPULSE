#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
    changeState(MAIN_MENU); 
    gameVariables = GameVariables::getInstance();

    //entities.cars.push_back(new Entity);
    physicsEngine = PhysicsEngine::getInstance();
    //physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
	//renderingEngine->initializeGL();
    renderingEngine->createLight_MainMenu();

    prevTime = 0;
    WAIT_TIME = 50;
    buttonPressed = false;
}

void MainMenuState::update(float dt)
{    

}

void MainMenuState::render()
{   
    //int curMenuButton = 0;
    //bool clicked = 0;

	if (renderingEngine->drawMainMenuScreen(curSelected, 0) == 1)
    {
        switch (curSelected)
        {
        case 0:
            changeState(PLAY);
            break;
        case 1:
            //This should bring up a profile screen
            if (gameVariables->getPlayerNum() < 2)
            {gameVariables->addPlayerTwo();printf("addedP2: %i\n",gameVariables->getPlayerNum() );}
            //else set player 2 slot to be default player 2
            changeState(PLAY); 
            break;
        case 2:
            changeState(MAIN_MENU); 
            break;
        case 3:
            changeState(MAIN_MENU); 
            break;
        case 4:
            changeState(MAIN_MENU); 
            break;
        }
    }
}


bool MainMenuState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    int MaxSelected = 5;


    //Non-Console
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if ((keyPressed == SDLK_LEFT) || (keyPressed == SDLK_a))
            {
                curSelected = curSelected - 1;
                if (curSelected < 0){curSelected = MaxSelected;}
                
            }
            else if ((keyPressed == SDLK_RIGHT) || (keyPressed == SDLK_d))
            {
                curSelected = curSelected + 1;
                if (curSelected > MaxSelected){curSelected = 0;}
            }
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
            {
                renderingEngine->startFadeOut();
            }

                

        }


    return true;
}

void MainMenuState::handleXboxEvents(int player,XboxController* state)
{    
    int MaxSelected = 5;
    if(state->dpadLeft || state->leftStick.x < 0)
    {
        if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
        {
            if(!buttonPressed)
                buttonPressed = true;
            curSelected = curSelected - 1;
            if (curSelected < 0){curSelected = MaxSelected;}
        }
        prevTime = clock.getCurrentTime();
    }
    else if(state->dpadRight || state->leftStick.x > 0)
    {
        if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
        {
            if(!buttonPressed)
                buttonPressed = true;
            curSelected = curSelected + 1;
            if (curSelected > MaxSelected){curSelected = 0;}
        }
        prevTime = clock.getCurrentTime();
    }
    else if (state->a)
    {
        renderingEngine->startFadeOut();
    }
}

MainMenuState* MainMenuState::getInstance()
{    
     printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
    return &MainMenuState;
}