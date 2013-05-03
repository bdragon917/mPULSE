#include <GameStates/MainMenuState.h>

MainMenuState::MainMenuState()
{
    //changeState(MAIN_MENU); 
    quit = false;
    gameVariables = GameVariables::getInstance();

    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
    renderingEngine->createLight_MainMenu();
}

void MainMenuState::initialize()
{
    prevTime = 0;
    WAIT_TIME = 250;
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
	/*
    psi.title = "Player 1 Profile";
    psi.profilesOnScreen[0] = "";
    psi.profilesOnScreen[1] = "";
    psi.profilesOnScreen[2] = "";
    psi.profilesOnScreen[3] = "";
    psi.profilesOnScreen[4] = "";
    psi.selectedItem = 0;
    psi.selectedTextTexture = 1;
    psi.selectedButtonTexture = 1;
	*/
    //assumes myDt is updated
    int retMenuVal = renderingEngine->drawMainMenuScreen(curSelected, 0, myDt, psi);     //retMenuVal returns 1 if it is finished (This means change screen!)

    //If all animation is finished, run the command
	if ((retMenuVal == 1) || endState)
    {
        lockControls = false;    //Unlock controls so main menu can be used again later
        endState = false;        //reset so it doesn't prevent this state from shuttingdown right away if called again

        switch (curSelected)
        {
        case 0:
			gameVariables->setNumPlayers(1);
			gameVariables->setProfileCurrentPlayer(1);
			/*
            for (int i = 0;i < gameVariables->getPlayerNum(); i++)
                {gameVariables->removePlayer(i);}               //Clears all players. HACK to make things work [Pushes responsibility of players management to profiles]
            gameVariables->addPlayers(new Profile());
			*/
			printf("case 0 triggered!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            changeState(PROFILE);
            break;
        case 1:
			gameVariables->setNumPlayers(2);
			gameVariables->setProfileCurrentPlayer(1);
			/*
            for (int i = 0;i < gameVariables->getPlayerNum(); i++)
                gameVariables->removePlayer(i);               //Clears all players. HACK to make things work [Pushes responsibility of players management to profiles]

            gameVariables->addPlayers(new Profile());
            gameVariables->addPlayerTwo();
			*/
			printf("case 1 triggered!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            changeState(PROFILE); 
            break;
        case 2:
            changeState(STORY);
            break;
        case 3:
            changeState(SETTING); 
            break;
        case 4:
            //quit = true;
            changeState(CREDITS); 
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
    if(player==0)
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
                    prevTime = clock.getCurrentTime();
                }            
            }
            else if(state->dpadRight || state->leftStick.x > 0)
            {
                if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
                {
                    if(!buttonPressed)
                        buttonPressed = true;
                    keySelectRight();
                    prevTime = clock.getCurrentTime();
                }
            }
            else if (state->a)
                keySelectTarget();
            else 
                buttonPressed = false;
        }
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
    else if (curSelected == 4)  //quit
    {
        soundEngine->FadeOutMusic(1000);
        renderingEngine->startTransition(RenderingEngine::FADE_OUT);
        lockControls = true;
    }
    else
    {
		renderingEngine->startTransition(RenderingEngine::FADE_OUT);
        lockControls = true;
    }
    //lock controls
}


MainMenuState* MainMenuState::getInstance()
{    
    printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
	MainMenuState.initialize();
    return &MainMenuState;
}
