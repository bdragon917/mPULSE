#include <GameStates/ProfileState.h>

ProfileState::ProfileState()
{
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
}

void ProfileState::initialize()
{
	PROFILE_FRAME_SIZE = 8;
	WAIT_TIME = 100;

	//Construct ProfileScreenInfo (Using this to tell renderingHowTo draw profile)
	psi.isActive = true;
    psi.title = "Player " + renderingEngine->FloatToString(gameVariables->getProfileCurrentPlayer()) + " Profile";

	currentFrame = 0;
	currentSelected = 0;

	buttonPressed = false;
    lockControls = false;
    goBack = false;

	prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)
}


void ProfileState::update(float dt)
{    
    myDt = dt;
}

void ProfileState::render()
{   
	
    if (gameVariables->profiles.size() < PROFILE_FRAME_SIZE)
        maxSelected = gameVariables->profiles.size();           //Change this depending on number of profiles avaliable
	else
		maxSelected = PROFILE_FRAME_SIZE;

	psi.numProfiles = maxSelected;

    for (int p=0; p<maxSelected; p++)
    {
        psi.profilesOnScreen[p] = gameVariables->profiles.at(p + currentFrame)->data.driverName;
    }

	if(currentFrame > 0)
		psi.canScrollUp = true;
	else
		psi.canScrollUp = false;


	if((currentFrame + PROFILE_FRAME_SIZE) < gameVariables->profiles.size() )
		psi.canScrollDown = true;
	else
		psi.canScrollDown = false;


    psi.selectedItem = currentSelected;



    //asumes myDt is updated
    int retMenuVal = renderingEngine->drawMainMenuScreen(5, 0, myDt, psi);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]


    //If all animation is finished, run the command
	if (retMenuVal == 1)
    {
		if(goBack)
		{
			if(gameVariables->getProfileCurrentPlayer() == 2)
			{
				gameVariables->setProfileCurrentPlayer(1);
				changeState(PROFILE);
				initialize();
			}
			else
			{
				changeState(MAIN_MENU);
			}
		}
		else
		{
			if ((gameVariables->getProfileCurrentPlayer() == 1) && (gameVariables->getNumPlayers() == 2))
			{
				gameVariables->setProfileCurrentPlayer(2);
				changeState(PROFILE);
				initialize();
			}
			else
			{
				changeState(SHOP);
			}
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

            if ((keyPressed == SDLK_UP) || (keyPressed == SDLK_w))
                upPressed();
            else if ((keyPressed == SDLK_DOWN) || (keyPressed == SDLK_s))
                downPressed();
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
                selectPressed();
            else if ((keyPressed == SDLK_ESCAPE))
                backPressed();
        }
    }
    return true;
}

void ProfileState::handleXboxEvents(int player,XboxController* state)
{   
    if(!lockControls)
    {
        bool* controllers = gameVariables->getControllers();

        if(state->dpadUp || state->leftStick.y > 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
				upPressed();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadDown || state->leftStick.y < 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                downPressed();
            }
            prevTime = clock.getCurrentTime();
        }
        else if (state->a)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                selectPressed();
            }
            prevTime = clock.getCurrentTime();
        }
        else if (state->b)
		{
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                backPressed();
            }
            prevTime = clock.getCurrentTime();
		}
    }
}


void ProfileState::upPressed()
{
	if(currentSelected == 0)
	{
		if(currentFrame == 0)
		{
			//Play a "not possible" sound
		}
		else
		{
			soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
			currentFrame--;
		}
	}
	else
	{
		soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
		currentSelected--;
	}
	printf("currentSelected: %i\n", currentSelected);
	//printf("%s",gameVariables->profiles.at(currentFrame+currentSelected)->data.driverName);
}


void ProfileState::downPressed()
{
	if(currentSelected == maxSelected-1)
	{
		if((currentFrame + PROFILE_FRAME_SIZE) >= gameVariables->profiles.size())
		{
			//Play a "not possible" sound
		}
		else
		{
			soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
			currentFrame++;
		}
	}
	else
	{
		soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
		currentSelected++;
	}
	printf("currentSelected: %i\n", currentSelected);
	//printf("%s",gameVariables->profiles.at(currentFrame+currentSelected)->data.driverName);
}


void ProfileState::selectPressed()
{
    Profile* profile = gameVariables->profiles.at(currentFrame + currentSelected);

    gameVariables->setPlayerProfile(profile, gameVariables->getProfileCurrentPlayer());          //This is the orginal code

    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
	//Instead of fadeOut we will make a generic leaving the state call.
	renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    lockControls = true;
}


void ProfileState::backPressed()
{
	renderingEngine->startTransition(RenderingEngine::INSTANT);
    lockControls = true;
	goBack = true;
}


ProfileState* ProfileState::getInstance()
{    
    printf("Profile state\n");
    static ProfileState ProfileState;
    ProfileState.changeState(PROFILE);

	ProfileState.initialize();

    return &ProfileState;
}
