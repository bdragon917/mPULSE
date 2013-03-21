#include <GameStates/ProfileState.h>

ProfileState::ProfileState()
{
    changeState(MAIN_MENU); 
    gameVariables = GameVariables::getInstance();
;
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
    //renderingEngine->createLight_MainMenu();

    //Load Profiles
    //TODO


    //Construct ProfileScreenInfo (Using this to tell renderingHowTo draw profile
    //Not reallly used excepted for .isActive, but good to initial the variables
    ProfileScreenInfo psi = ProfileScreenInfo();
    psi.isActive = true;
    psi.title = "Player 1 Profile";
    psi.profilesOnScreen[0] = "";
    psi.profilesOnScreen[1] = "";
    psi.profilesOnScreen[2] = "";
    psi.profilesOnScreen[3] = "";
    psi.profilesOnScreen[4] = "";
    psi.selectedItem = 0;               //0 is the done button, the others are used for the possible items
    psi.selectedTextTexture = 1;
    psi.selectedButtonTexture = 1;

    curSelected = 1;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_SELECTED = 4;           //Change this depending on number of profiles avaliable
    buttonPressed = false;
    lockControls = false;
    endState = false;

}

void ProfileState::update(float dt)
{    
    myDt = dt;
}

void ProfileState::render()
{   
    psi.isActive = true;
    psi.selectedItem = curSelected;


    //asumes myDt is updated
    int retMenuVal = renderingEngine->drawMainMenuScreen(5, 0, myDt, psi);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]


    //If all animation is finished, run the command
	if ((retMenuVal == 1) || endState)
    {
        lockControls = false;    //Unlock controls so main menu can be used again later
        endState = false;       //reset so this state can be called again

        switch (curSelected)
        {
        case 0:
            //changeState(PLAY);
            break;
        case 1:
            //This should bring up a profile screen
            if (gameVariables->getPlayerNum() < 2)
            {
                //changeState(PLAY); 
            }
            else
            {
                //changeState(PLAY); 
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
     
}

bool ProfileState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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

void ProfileState::handleXboxEvents(int player,XboxController* state)
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

        if(state->dpadUp || state->leftStick.y > 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectLeft();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadDown || state->leftStick.y < 0)
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
        else if (state->b)
            backPressed();
    }
}


void ProfileState::keySelectLeft()
{
    curSelected = curSelected - 1;
    if (curSelected < 0){curSelected = MAX_SELECTED;}
}

void ProfileState::keySelectRight()
{
    curSelected = curSelected + 1;
    if (curSelected > MAX_SELECTED){curSelected = 0;}
}

void ProfileState::keySelectTarget()
{
    if (curSelected == 0)
    {
        //Finish Profile state
        changeState(PLAY);
    }
    else
    {
        //Load profile
    }

}

void ProfileState::backPressed()
{
    changeState(MAIN_MENU);
}
ProfileState* ProfileState::getInstance()
{    
     printf("Profile state\n");
    static ProfileState ProfileState;
    ProfileState.changeState(PROFILE);
    return &ProfileState;
}
