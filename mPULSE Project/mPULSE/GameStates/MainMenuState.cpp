#include <GameStates/MainMenuState.h>

MainMenuState::MainMenuState()
{
    changeState(MAIN_MENU); 
    gameVariables = GameVariables::getInstance();

    //entities.cars.push_back(new Entity);
    physicsEngine = PhysicsEngine::getInstance();
    //physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
	//renderingEngine->initializeGL();
    renderingEngine->createLight_MainMenu();

    curSelected = 0;
    prevTime = 0;
    WAIT_TIME = 50;
    MAX_SELECTED = 4;
    buttonPressed = false;
    endState = false;          //might not be used....
    lockControls = false;
}

void MainMenuState::update(float dt)
{    
    myDt = dt;
}

void MainMenuState::render()
{   
    renderingEngine->createLight_MainMenu();

    //Construct ProfileScreenInfo (Using this to tell renderingHowTo draw profile
    //Not reallly used excepted for .isActive, but good to initial the variables
    ProfileScreenInfo psi = ProfileScreenInfo();
    psi.isActive = false;
    psi.title = "Player 1 Profile";
    psi.profilesOnScreen[0] = "";
    psi.profilesOnScreen[1] = "";
    psi.profilesOnScreen[2] = "";
    psi.profilesOnScreen[3] = "";
    psi.profilesOnScreen[4] = "";
    psi.selectedItem = 0;
    psi.selectedTextTexture = 1;
    psi.selectedButtonTexture = 1;



    //asumes myDt is updated
    int retMenuVal = renderingEngine->drawMainMenuScreen(curSelected, 0, myDt, psi);     //retMenuVal returns 1 if it is finished (This means change screen!)


    //If all animation is finished, run the command
	if ((retMenuVal == 1) || endState)
    {
        lockControls = false;    //Unlock controls so main menu can be used again later
        endState = false;        //reset so it doesn't prevent this state from shuttingdown right away if called again

        switch (curSelected)
        {
        case 0:
            changeState(PROFILE);
            break;
        case 1:
            //This should bring up a profile screen
            //if (gameVariables->getPlayerNum() < 2)
            //{
            //    printf("Only one player detected.\n");//TODO Tell the player on screen they need more controllers.
            //    gameVariables->addPlayerTwo();
            //    gameVariables->player2isAI = true;
            //    changeState(PROFILE); 
            //}
            //else
            //{
                gameVariables->addPlayerTwo();
                changeState(PROFILE); 
           // }
            break;
        case 2:
            changeState(STORY);
            break;
        case 3:
            changeState(SETTING); 
            break;
        case 4:
            //changeState(MAIN_MENU); 
            break;
        }
    }

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

        //if(state->start && !controllers[player])
        //{
        //    //TODO: ask for player profile
        //    gameVariables->addPlayer(player);
       // }
        //if(state->back && controllers[player])
       //     gameVariables->removePlayer(player);

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
    soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelected = curSelected - 1;
    if (curSelected < 0){curSelected = MAX_SELECTED;}
}

void MainMenuState::keySelectRight()
{
    soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelected = curSelected + 1;
    if (curSelected > MAX_SELECTED){curSelected = 0;}
}

void MainMenuState::keySelectTarget()
{
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
    if (curSelected == 0)
    {
        endState = true;
    }
    else if (curSelected == 1)
    {
        endState = true;
    }
    else
    {
        renderingEngine->startFadeOut();
        lockControls = true;
    }
    //lock controls
}


MainMenuState* MainMenuState::getInstance()
{    
     printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
    return &MainMenuState;
}
