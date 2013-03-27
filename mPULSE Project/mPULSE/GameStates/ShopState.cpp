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

    //ssi = new ssi???
    ssi.di.clear();

    //texture 42 is mechanic =)
    mechanicGirl = new DynamicImage(-125,400,0,20,20, 42,0 );   //will probably be overwritten in reset(), so change the values there
    painterGirl = new DynamicImage(-50,50,0,20,20, 43,0 );

    mechanicGirl->setTargetLocation(250,400,0);
    mechanicGirl->setMode(1);

    ssi.di.push_back(mechanicGirl);
}

void ShopState::reset()
{
    ssi.di.clear();
    enterMechanic();
}

void ShopState::enterMechanic()
{
    mechanicGirl->setLocation(-125,600,0);
    mechanicGirl->setTargetLocation(200,600,0);
    ssi.di.push_back(mechanicGirl);
}

void ShopState::enterPainter()
{
    painterGirl->setLocation(-385.5f,96,0);
    painterGirl->setTargetLocation(200.5f,600,0);
    ssi.di.push_back(painterGirl);
}

void ShopState::update(float dt)
{    
    //printf("x:%i y:%i\n",curSelectedX, curSelectedY );
}

void ShopState::render()
{   
    renderingEngine->createLight_MainMenu();

    int retMenuVal = renderingEngine->drawShopScreen(myDt, ssi);    //retMenuVal returns 1 if it is finished (This means change screen!) [5 is to not show selected on main menu]

    if (retMenuVal == 1)
    {
        switch (curSelectedY)
        {
        case -1:    //back
            lockControls = false;
            curSelectedY = 1;
            changeState(MAIN_MENU);
            break;
        default:
            lockControls = false;
            curSelectedY = 1;
            changeState(STAGE);
        }
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
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                keySelectTarget();
        }
        else if ((state->b)||(state->back))
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME)
                backPressed();
        }
    }
}


void ShopState::keySelectLeft()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedX -= 1;

    if (curSelectedX < 0)
        curSelectedX = MAX_X_SELECTED;
}

void ShopState::keySelectRight()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedX += 1;

    if (curSelectedX > MAX_X_SELECTED)
        curSelectedX = 0;
}

void ShopState::keySelectUp()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedY -= 1;

    if (curSelectedY < 0)
        curSelectedY = MAX_Y_SELECTED;
}

void ShopState::keySelectDown()
{
     soundEngine->playSound(4,7);    //4 is channel, 7 is index for lazer
    curSelectedY += 1;

    if (curSelectedY > MAX_Y_SELECTED)
        curSelectedY = 0;
}

void ShopState::keySelectTarget()
{
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
    renderingEngine->startFadeOut();
    lockControls = true;
}

void ShopState::backPressed()
{
    lockControls = true;
    curSelectedY = -1;
    renderingEngine->startFadeOut();
}
ShopState* ShopState::getInstance()
{    
     printf("Shop state\n");
    static ShopState ShopState;
    ShopState.changeState(SHOP);
    ShopState.reset();
    return &ShopState;
}
