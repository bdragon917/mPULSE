#include <GameStates/SettingState.h>

SettingState::SettingState()
{
    changeState(SETTING);
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
 
    curSelectedY = 1;
    curSelectedX = 0;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_X_SELECTED = 4;           //Change this depending on number of profiles avaliable
    MAX_Y_SELECTED = 4;

    buttonPressed = false;
    lockControls = false;
    endState = false;

}

void SettingState::update(float dt)
{    
    printf("x:%i y:%i\n",curSelectedX, curSelectedY );
}

void SettingState::render()
{   
    renderingEngine->createLight_MainMenu();

    int retMenuVal = renderingEngine->drawSettingScreen(myDt, 0, 0);    //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        changeState(MAIN_MENU);
    }


}

bool SettingState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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
            else if ((keyPressed == SDLK_UP) || (keyPressed == SDLK_w))
            {
                keySelectUp();  
            }
            else if ((keyPressed == SDLK_DOWN) || (keyPressed == SDLK_s))
            {
                keySelectDown();
            }
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
                keySelectTarget();
        }
    }
    return true;
}

void SettingState::handleXboxEvents(int player,XboxController* state)
{   
    if(!lockControls)
    {
        
        bool* controllers = gameVariables->getControllers();

        if(state->dpadUp || state->leftStick.y > 0.5f)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectUp();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadDown || state->leftStick.y < -0.5f)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectDown();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadLeft || state->leftStick.x < -0.5f)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                keySelectLeft();
            }
            prevTime = clock.getCurrentTime();
        }
        else if(state->dpadRight || state->leftStick.x > 0.5f)
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


void SettingState::keySelectLeft()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    if (curSelectedY == 1)
    {
        //Does Resolution Stuff
        if (gameVariables->curResolution = gameVariables->LAST)
        {gameVariables->curResolution = gameVariables->STANDARD;}
    }
    if (curSelectedY == 2)
    {gameVariables->numberOfAIs -= 1;}
    /*
    curSelectedX -= 1;

    if (curSelectedX < 0)
        curSelectedX = MAX_X_SELECTED;
        */

}

void SettingState::keySelectRight()
{
  soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    if (curSelectedY == 1)
    {
        int index = gameVariables->curResolution + 1;
        gameVariables->curResolution = (GameVariables::Resolution)(gameVariables->curResolution + 1);
        //Does Resolution Stuff
        if (gameVariables->curResolution = gameVariables->LAST)
        {gameVariables->curResolution = gameVariables->STANDARD;}
    }
    if (curSelectedY == 2)
    {gameVariables->numberOfAIs += 1;}
    
    /*
    curSelectedX += 1;

    if (curSelectedX > MAX_X_SELECTED)
        curSelectedX = 0;
        */
}

void SettingState::keySelectUp()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedY -= 1;

    if (curSelectedY < 0)
        curSelectedY = MAX_Y_SELECTED;
}

void SettingState::keySelectDown()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedY += 1;

    if (curSelectedY > MAX_Y_SELECTED)
        curSelectedY = 0;
}

void SettingState::keySelectTarget()
{
    //changeState(PLAY);
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
    renderingEngine->startFadeOut();
}

void SettingState::backPressed()
{
    changeState(MAIN_MENU);
}
SettingState* SettingState::getInstance()
{    
     printf("Settings state\n");
    static SettingState SettingState;
    SettingState.changeState(SETTING);
    return &SettingState;
}
