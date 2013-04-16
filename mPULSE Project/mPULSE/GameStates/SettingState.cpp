#include <GameStates/SettingState.h>

SettingState::SettingState()
{
    changeState(SETTING);
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
 
    curSelectedY = 0;
    curSelectedX = 0;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

    WAIT_TIME = 50;
    MAX_X_SELECTED = 4;
    MAX_Y_SELECTED = 3;

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

    int retMenuVal = renderingEngine->drawSettingScreen(myDt, curSelectedX, curSelectedY);    //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        if(curSelectedY == 2)
            changeState(CONTROLS);
        else
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
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                keySelectTarget();
        }
        else if (state->b)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                backPressed();
        }
    }
}


void SettingState::keySelectLeft()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer

    if (curSelectedY == 0)      //resolution
    {
        //HACK for Looping through resolutions
        if (gameVariables->curResolution == gameVariables->STANDARD)
            gameVariables->curResolution = gameVariables->LAPTOP;
        else if (gameVariables->curResolution == gameVariables->LAPTOP)
            gameVariables->curResolution = gameVariables->GAMELAB;
        else
            gameVariables->curResolution = gameVariables->STANDARD;

        //Does resolution stuff
    }
    else if (curSelectedY == 1)      //Fullscreen
    {
        if (gameVariables->isFullScreen){gameVariables->isFullScreen = false;}else{gameVariables->isFullScreen = true;}
    }


    /*
    curSelectedX -= 1;

    if (curSelectedX < 0)
        curSelectedX = MAX_X_SELECTED;
      */  

}

void SettingState::keySelectRight()
{
  soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer


    if (curSelectedY == 0)      //resolution
    {
        //HACK for Looping through resolutions
        if (gameVariables->curResolution == gameVariables->STANDARD)
            gameVariables->curResolution = gameVariables->GAMELAB;
        else if (gameVariables->curResolution == gameVariables->LAPTOP)
            gameVariables->curResolution = gameVariables->STANDARD;
        else
            gameVariables->curResolution = gameVariables->LAPTOP;

        //Does resolution stuff
    }
    else if (curSelectedY == 1)      //Fullscreen
    {
        if (gameVariables->isFullScreen){gameVariables->isFullScreen = false;}else{gameVariables->isFullScreen = true;}
    }
    
    
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

    if (curSelectedY == 0)
    {
        reinitializeWindow();
    }
    else if (curSelectedY == 1)
    {
        reinitializeWindow();
    }
    else if(curSelectedY == 2)
    {
        renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    }
    else if (curSelectedY == 3)     //Done
    {
        renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    }

    
}

void SettingState::backPressed()
{
    renderingEngine->startTransition(RenderingEngine::FADE_OUT);
    curSelectedY = 3;
}
SettingState* SettingState::getInstance()
{    
     printf("Settings state\n");
    static SettingState SettingState;
    SettingState.changeState(SETTING);
    return &SettingState;
}




void SettingState::reinitializeWindow()
{
        SDL_Init( SDL_INIT_EVERYTHING );

	//Initalization for motion blur
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	//Create Main Window

    int xResolution;
    int yResolution;

    switch (gameVariables->curResolution)
    {
        case gameVariables->STANDARD:
            //xResolution = 640; yResolution = 480;renderingEngine->ChangeResolution(640, 480);break;
            xResolution = 1280; yResolution = 960;renderingEngine->ChangeResolution(1280, 960);break;
        case gameVariables->LAPTOP:
            xResolution = 1600; yResolution = 900;renderingEngine->ChangeResolution(1600, 900);break;
        case gameVariables->GAMELAB:
            xResolution = 1920; yResolution = 1200;renderingEngine->ChangeResolution(1920, 1200);break;
    }
    SDL_Surface* screen;

    if (gameVariables->isFullScreen)
        screen = SDL_SetVideoMode(xResolution, yResolution, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode(xResolution, yResolution, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	
    
    if (screen != NULL)
        SDL_WM_SetCaption("mPULSE","mPULSE");

    renderingEngine->initializeGL();
}
