#include <GameStates/ResultState.h>

ResultState::ResultState()
{
    changeState(RESULT); 
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
}

void ResultState::initialize()
{
	curSelected = 0;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_SELECTED = 4;           //Change this depending on number of profiles avaliable
    buttonPressed = false;
    lockControls = false;
    endState = false;

	gameVariables->saveProfiles();
}


void ResultState::update(float dt)
{    


	// We want to save the number of Obs earned during the race into the profile
}

void ResultState::render()
{   
    renderingEngine->createLight_MainMenu();
    int retMenuVal = renderingEngine->drawResultScreen(myDt);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        lockControls = false;
        changeState(LOUNGE);
    }


}

bool ResultState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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
        }
    }
    return true;
}

void ResultState::handleXboxEvents(int player,XboxController* state)
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
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                keySelectTarget();
        else if (state->b)
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                backPressed();
    }
}


void ResultState::keySelectLeft()
{
}

void ResultState::keySelectRight()
{
}

void ResultState::keySelectTarget()
{
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
	renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    lockControls = true;
}

void ResultState::backPressed()
{
    changeState(MAIN_MENU);
}
ResultState* ResultState::getInstance()
{    
     printf("ResultState state\n");
    static ResultState resultState;
    resultState.changeState(RESULT);
	resultState.initialize();
    return &resultState;
}
