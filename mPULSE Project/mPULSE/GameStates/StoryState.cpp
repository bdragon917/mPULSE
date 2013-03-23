#include <GameStates/StoryState.h>

StoryState::StoryState()
{
    changeState(STORY); 
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
 
    curSelected = 0;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_SELECTED = 4;           //Change this depending on number of profiles avaliable
    buttonPressed = false;
    lockControls = false;
    endState = false;

}

void StoryState::update(float dt)
{    

}

void StoryState::render()
{   
    renderingEngine->createLight_MainMenu();
    int retMenuVal = renderingEngine->drawStoryScreen(myDt);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        changeState(MAIN_MENU);
    }


}

bool StoryState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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

void StoryState::handleXboxEvents(int player,XboxController* state)
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


void StoryState::keySelectLeft()
{
}

void StoryState::keySelectRight()
{
}

void StoryState::keySelectTarget()
{
    //changeState(PLAY);
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
    renderingEngine->startFadeOut();
}

void StoryState::backPressed()
{
    changeState(MAIN_MENU);
}
StoryState* StoryState::getInstance()
{    
     printf("Story state\n");
    static StoryState StoryState;
    StoryState.changeState(STORY);
    return &StoryState;
}
