#include <GameStates/StageSelectState.h>

StageSelectState::StageSelectState()
{
    changeState(STAGE); 
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
 
    int curSelectedX = 0;
    int curSelectedY = 0;

    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_X_SELECTED = 4; 
    MAX_Y_SELECTED = gameVariables->loadedTracks->getNumberofTracks() + 1; 
    buttonPressed = false;
    lockControls = false;
    endState = false;

}

void StageSelectState::update(float dt)
{    

}

void StageSelectState::render()
{   
    renderingEngine->createLight_MainMenu();
    int retMenuVal = renderingEngine->drawStageSelectScreen(myDt, curSelectedY);     //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        switch (curSelectedY)
        {
        case -1:
            curSelectedY = 1;
            lockControls = false;
            changeState(SHOP);
            break;
        default:
            PlayState* pStage = PlayState::getInstance();
            pStage->resetAll();
            renderingEngine->resetFade();   //In case
            lockControls = false;
            changeState(PLAY);
            break;
        }
    }


}

bool StageSelectState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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

void StageSelectState::handleXboxEvents(int player,XboxController* state)
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
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                keySelectTarget();
        }
        else if (state->b)
            backPressed();
    }
}


void StageSelectState::keySelectLeft()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
     curSelectedY = curSelectedY - 1;
     if (curSelectedY < 0)
     {curSelectedY = gameVariables->loadedTracks->getNumberofTracks();}
}

void StageSelectState::keySelectRight()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
     curSelectedY = curSelectedY + 1;
     if (curSelectedY > gameVariables->loadedTracks->getNumberofTracks())
     {curSelectedY = 0;}
}

void StageSelectState::keySelectTarget()
{
    if (curSelectedY == 0)
    {
        soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
        renderingEngine->startFadeOut();
        lockControls = true;
    }
    else
    {
        gameVariables->selectedTrack = curSelectedY - 1;


        soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
        renderingEngine->startFadeOut();
        lockControls = true;
        //load the selected track!!!
    }
}

void StageSelectState::backPressed()
{
    curSelectedY = -1;
    renderingEngine->startFadeOut();
    lockControls = true;
}
StageSelectState* StageSelectState::getInstance()
{    
     printf("StageSelectState state\n");
    static StageSelectState StageSelectState;
    StageSelectState.changeState(STAGE);
    return &StageSelectState;
}
