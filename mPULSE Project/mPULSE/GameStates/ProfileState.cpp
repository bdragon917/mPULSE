#include <GameStates/ProfileState.h>

ProfileState::ProfileState()
{
    changeState(MAIN_MENU); 
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
    profilesOffset = 0;

    //renderingEngine->createLight_MainMenu();

    //Load Profiles
    //TODO


    //Construct ProfileScreenInfo (Using this to tell renderingHowTo draw profile
    //Not reallly used excepted for .isActive, but good to initial the variables
    //ProfileScreenInfo psi = ProfileScreenInfo();
    psi.isActive = true;
    psi.title = "Player " + renderingEngine->FloatToString(gameVariables->profileTargetPlayer) + " Profile";
    psi.profilesOnScreen[0] = "Default";


    const int MaxShown = 6;     //should be array - 2
    if (gameVariables->profiles.size() < MaxShown)
    {
        MAX_SELECTED = gameVariables->profiles.size() + 1;           //Change this depending on number of profiles avaliable

        for (unsigned p=0;p<gameVariables->profiles.size();p++)
        {
            psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p)->data.driverName;
        }
    }
    else
    {
        if (profilesOffset != 0)
        {psi.profilesOnScreen[0] = "Move Up";}

        for (int p=0;p<MaxShown;p++)
        {
            psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p+profilesOffset)->data.driverName;
        }
        psi.profilesOnScreen[7] = "Scroll Down";
        MAX_SELECTED = 8;           //Change this depending on number of profiles avaliable     //so 8 is a special case, this should move down
    }






    psi.selectedItem = 1;               //0 is the done button, the others are used for the possible items
    psi.selectedTextTexture = 1;
    psi.selectedButtonTexture = 1;

    curSelected = 1;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    

    //MAX_SELECTED = Gamevariables.profileNum + 2;
    //load profiles 0 to max, or 3 tp profiles on screen {not 0, not 1, 2 +}
    //if more than number possible, add additional one that says "SHOW MORE", and increment MAX_SELECTED []

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

    psi.title = "Player " + renderingEngine->FloatToString(gameVariables->profileTargetPlayer) + " Profile";

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
            //Finish Profile state
            if ((gameVariables->profileTargetPlayer == 1)&&(gameVariables->getPlayerNum() == 2))
            {
                gameVariables->profileTargetPlayer = 2;
                curSelected = 1;
                changeState(PROFILE);
            }
            else
            {
                gameVariables->profileTargetPlayer = 1;
                curSelected = 1;
                changeState(SHOP);
            }
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
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelected = curSelected - 1;
    if (curSelected < 0){curSelected = MAX_SELECTED;}
}

void ProfileState::keySelectRight()
{
    printf("curSelected: %i\n", curSelected);
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelected = curSelected + 1;
    if (curSelected > MAX_SELECTED){curSelected = 0;}
}

void ProfileState::keySelectTarget()
{
    if (curSelected == 0)
    {
        soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
        renderingEngine->startFadeOut();
        lockControls = true;
    }
    else
    {
        if (curSelected == 1)
        {
                if (profilesOffset != 0)
                {
                    if (profilesOffset != 0)
                    {profilesOffset = profilesOffset - 1;}

                    

                    printf("profilesOffset: %i\n", profilesOffset);
                
                        psi.profilesOnScreen[0] = "Default";

                        const int MaxShown = 6;     //should be array - 2
                        if (gameVariables->profiles.size() < MaxShown)
                        {
                            for (unsigned p=0;p<gameVariables->profiles.size();p++)
                            {
                                psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p)->data.driverName;
                            }
                        }
                        else
                        {
                            if (profilesOffset != 0)
                            {psi.profilesOnScreen[0] = "Move Up";}

                            for (int p=0;p<MaxShown;p++)
                            {
                                psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p+profilesOffset)->data.driverName;
                            }
                            psi.profilesOnScreen[7] = "Scroll Down";
                            MAX_SELECTED = 8;           //Change this depending on number of profiles avaliable     //so 8 is a special case, this should move down
                        }
                
                }
                else
                {
                    printf("use default");
                    //use default
                }
        }
        else if (curSelected == 8) 
        {
            const unsigned MaxShown = 6;     //should be array - 2

                    if ((profilesOffset) < (gameVariables->profiles.size() - MaxShown))
                    {profilesOffset = profilesOffset + 1;}
                    printf("profilesOffset: %i\n", profilesOffset);
                
                        psi.profilesOnScreen[0] = "Default";

                        
                        if (gameVariables->profiles.size() < MaxShown)
                        {
                            for (unsigned p=0;p<gameVariables->profiles.size();p++)
                            {
                                psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p)->data.driverName;
                            }
                        }
                        else
                        {
                            if (profilesOffset != 0)
                            {psi.profilesOnScreen[0] = "Move Up";}

                            for (int p=0;p<MaxShown;p++)
                            {
                                psi.profilesOnScreen[p+1] = gameVariables->profiles.at(p+profilesOffset)->data.driverName;
                            }
                            psi.profilesOnScreen[7] = "Scroll Down";
                            MAX_SELECTED = 8;           //Change this depending on number of profiles avaliable     //so 8 is a special case, this should move down
                        }
        }
        else
        {
            //printf("load profile %i out of %i\n", profilesOffset + curSelected - 2, gameVariables->profiles.size() );

            Profile* aProfile = gameVariables->profiles.at(profilesOffset + curSelected - 2);
            Profile::profileData dataaaaa = aProfile->data;
            std::string aNameeeee = dataaaaa.driverName;

            gameVariables->setPlayers(aProfile, targetPlayer);

            soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
            renderingEngine->startFadeOut();
            lockControls = true;
               //printf("load profile %i \n" + aNameeeee, profilesOffset + curSelected - 2);
        //Load profile
        }

    }

}

void ProfileState::backPressed()
{
    curSelected = 1;
    changeState(MAIN_MENU);
}
ProfileState* ProfileState::getInstance()
{    
     printf("Profile state\n");
    static ProfileState ProfileState;
    ProfileState.changeState(PROFILE);
    return &ProfileState;
}
