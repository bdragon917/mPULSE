#include <GameStates/LoungeState.h>

LoungeState::LoungeState()
{
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
}

void LoungeState::initialize()
{
	WAIT_TIME = 100;

	currentSelected = 0;
	maxSelected = 2;

	buttonPressed = false;
    lockControls = false;
    goBack = false;

	prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)
}


void LoungeState::update(float dt)
{    
    myDt = dt;
}

void LoungeState::render()
{   
    //asumes myDt is updated
    int retMenuVal = renderingEngine->drawLoungeScreen(myDt, currentSelected);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    //If all animation is finished, run the command
	if (retMenuVal == 1)
    {
		if(goBack)
		{
			changeState(MAIN_MENU);
		}
		else
		{
			switch (currentSelected)
			{
			case 0:
				changeState(SHOP);
				break;
			case 1:
				changeState(STAGE); 
				break;
			}
		}
    }
     
}

bool LoungeState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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

void LoungeState::handleXboxEvents(int player,XboxController* state)
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


void LoungeState::upPressed()
{
	if(currentSelected == 0)
	{
		//play sound for "not possible"
	}
	else
	{
		printf("shop selected\n");
		soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
		currentSelected = 0;
	}
}


void LoungeState::downPressed()
{
	if(currentSelected == 1)
	{
		//play sound for "not possible"
	}
	else
	{
		printf("race selected\n");
		soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
		currentSelected = 1;
	}
}


void LoungeState::selectPressed()
{
    soundEngine->playSound(3,11);
	renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    lockControls = true;
}


void LoungeState::backPressed()
{
	renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    lockControls = true;
	goBack = true;
}


LoungeState* LoungeState::getInstance()
{    
    printf("Lounge State\n");
    static LoungeState LoungeState;
    LoungeState.changeState(LOUNGE);

	LoungeState.initialize();

    return &LoungeState;
}
