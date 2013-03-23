#include <GameStates/ShopState.h>

ShopState::ShopState()
{
    changeState(SHOP); 
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

void ShopState::update(float dt)
{    
    //printf("x:%i y:%i\n",curSelectedX, curSelectedY );
}

void ShopState::render()
{   
    renderingEngine->createLight_MainMenu();

    int retMenuVal = renderingEngine->drawShopScreen(myDt);    //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {

        changeState(STAGE);
    }


}

bool ShopState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
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

void ShopState::handleXboxEvents(int player,XboxController* state)
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


void ShopState::keySelectLeft()
{
    curSelectedX -= 1;

    if (curSelectedX < 0)
        curSelectedX = MAX_X_SELECTED;
}

void ShopState::keySelectRight()
{
    curSelectedX += 1;

    if (curSelectedX > MAX_X_SELECTED)
        curSelectedX = 0;
}

void ShopState::keySelectUp()
{
    curSelectedY -= 1;

    if (curSelectedY < 0)
        curSelectedY = MAX_Y_SELECTED;
}

void ShopState::keySelectDown()
{
    curSelectedY += 1;

    if (curSelectedY > MAX_Y_SELECTED)
        curSelectedY = 0;
}

void ShopState::keySelectTarget()
{
    renderingEngine->startFadeOut();
}

void ShopState::backPressed()
{
    changeState(MAIN_MENU);
}
ShopState* ShopState::getInstance()
{    
     printf("Shop state\n");
    static ShopState ShopState;
    ShopState.changeState(SHOP);
    return &ShopState;
}
