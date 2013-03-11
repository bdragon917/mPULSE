#include <GameStates/MainMenuState.h>

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

    curSelected = 0;
    prevTime = 0;
    WAIT_TIME = 50;
    MAX_SELECTED = 4;
    buttonPressed = false;
    startGame = false;
}

void MainMenuState::update(float dt)
{    

}

void MainMenuState::render()
{   
    int retMenuVal = renderingEngine->drawMainMenuScreen(curSelected, 0);



	if ((retMenuVal == 1) || startGame)
    {
        switch (curSelected)
        {
        case 0:
            renderingEngine->startFadeOut();
            changeState(PLAY);
            break;
        case 1:
            //This should bring up a profile screen
            if (gameVariables->getPlayerNum() < 2)
                printf("Only one player detected.\n");//TODO Tell the player on screen they need more controllers.
            else
            {
                renderingEngine->startFadeOut();
                changeState(PLAY); 
            }
            break;
        case 2:
            //changeState(MAIN_MENU); 
            break;
        case 3:
            //changeState(MAIN_MENU); 
            break;
        case 4:
            //changeState(MAIN_MENU); 
            break;
        }
    }
     
    startGame = false;
}

bool MainMenuState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    startGame = false;

    //Non-Console
    if (KeyboardMouseEvents.type == SDL_KEYDOWN)
        {
        SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

        if ((keyPressed == SDLK_LEFT) || (keyPressed == SDLK_a))
        {
            curSelected = curSelected - 1;
            if (curSelected < 0){curSelected = MAX_SELECTED;}
                
        }
        else if ((keyPressed == SDLK_RIGHT) || (keyPressed == SDLK_d))
        {
            curSelected = curSelected + 1;
            if (curSelected > MAX_SELECTED){curSelected = 0;}
        }
        else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
            startGame = true;
        else if(keyPressed == SDLK_n)
            gameVariables->addPlayer(1);
    }
    return true;
}

void MainMenuState::handleXboxEvents(int player,XboxController* state)
{   
    if(!startGame)
    {
        
        bool* controllers = gameVariables->getControllers();

        if(state->start && !controllers[player])
            gameVariables->addPlayer(player);
        if(state->back && controllers[player])
            gameVariables->removePlayer(player);

        if(state->dpadLeft || state->leftStick.x < 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                curSelected = curSelected - 1;
                if (curSelected < 0){curSelected = MAX_SELECTED;}
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
                if (curSelected > MAX_SELECTED){curSelected = 0;}
            }
            prevTime = clock.getCurrentTime();
        }
        else if (state->a)
            startGame = true;
        else
            startGame = false;
    }
}

MainMenuState* MainMenuState::getInstance()
{    
     printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
    return &MainMenuState;
}
