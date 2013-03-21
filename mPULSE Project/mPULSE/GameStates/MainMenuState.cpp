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
    startGame = false;          //might not be used....
    lockControls = false;
}

void MainMenuState::update(float dt)
{    
    myDt = dt;
}

void MainMenuState::render()
{   
    //asumes myDt is updated
    int retMenuVal = renderingEngine->drawMainMenuScreen(curSelected, 0, myDt);     //retMenuVal returns 1 if it is finished (This means change screen!)


    //If all animation is finished, run the command
	if ((retMenuVal == 1))
    {
        lockControls = false;    //Unlock controls so main menu can be used again later
        switch (curSelected)
        {
        case 0:
            changeState(PLAY);
            break;
        case 1:
            //This should bring up a profile screen
            if (gameVariables->getPlayerNum() < 2)
            {
                printf("Only one player detected.\n");//TODO Tell the player on screen they need more controllers.
                gameVariables->addPlayerTwo();
                gameVariables->player2isAI = true;
                changeState(PLAY); 
            }
            else
            {
                gameVariables->addPlayerTwo();
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
    if (!lockControls)  //Allow control if user hasn't chose an option yet
    {

        //Non-Console
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
            {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if ((keyPressed == SDLK_LEFT) || (keyPressed == SDLK_a))
            {
                keySelectLeft();
                
            }
            else if ((keyPressed == SDLK_RIGHT) || (keyPressed == SDLK_d))
            {
                keySelectRight();
            }
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
                keySelectTarget();
            //else if(keyPressed == SDLK_n)
            //    gameVariables->addPlayer(1);
        }
    }
    return true;
}

void MainMenuState::handleXboxEvents(int player,XboxController* state)
{   
    if(!lockControls)
    {
        
        bool* controllers = gameVariables->getControllers();

        if(state->start && !controllers[player])
        {
            //TODO: ask for player profile
            gameVariables->addPlayer(player);
        }
        if(state->back && controllers[player])
            gameVariables->removePlayer(player);

        if(state->dpadLeft || state->leftStick.x < 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectLeft();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadRight || state->leftStick.x > 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectRight();
            }
            prevTime = clock.getCurrentTime();
        }
        else if (state->a)
            keySelectTarget();
    }
}


void MainMenuState::keySelectLeft()
{
    curSelected = curSelected - 1;
    if (curSelected < 0){curSelected = MAX_SELECTED;}
}

void MainMenuState::keySelectRight()
{
    curSelected = curSelected + 1;
    if (curSelected > MAX_SELECTED){curSelected = 0;}
}

void MainMenuState::keySelectTarget()
{
    renderingEngine->startFadeOut();
    lockControls = true;
    //lock controls
}


MainMenuState* MainMenuState::getInstance()
{    
     printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
    return &MainMenuState;
}
