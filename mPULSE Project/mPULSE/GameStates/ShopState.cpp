#include <GameStates/ShopState.h>

ShopState::ShopState()
{
    changeState(SHOP); 
    quit = false;
    gameVariables = GameVariables::getInstance();
    physicsEngine = PhysicsEngine::getInstance();
    renderingEngine = RenderingEngine::getInstance();
    soundEngine = SoundEngine::getInstance();
}


void ShopState::initialize()
{
	currentSelectedCategory = 0;
    currentSelectedItem = 0;
    prevTime = clock.getCurrentTime();  //So users don't accetentially select (as button is pressed from previous state)

	inSubmenu = false;

    WAIT_TIME = 50;
    MAX_CATEGORY_SELECTED = 4;           
    MAX_ITEM_SELECTED = 4;

    buttonPressed = false;
    lockControls = false;
    goBack = false;

    //ssi = new ssi???
    ssi.di.clear();

    //texture 42 is mechanic =)
    mechanicGirl = new DynamicImage(-125,400,0,20,20,42,1);   //will probably be overwritten in reset(), so change the values there
    painterGirl = new DynamicImage(-50,50,0,20,20,43,0);

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
        changeState(LOUNGE);
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
                leftPressed();  
            }
            else if ((keyPressed == SDLK_RIGHT) || (keyPressed == SDLK_d))
            {
                rightPressed();
            }
            else if ((keyPressed == SDLK_UP) || (keyPressed == SDLK_w))
            {
                upPressed();  
            }
            else if ((keyPressed == SDLK_DOWN) || (keyPressed == SDLK_s))
            {
                downPressed();
            }
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
                selectPressed();
            else if ((keyPressed == SDLK_ESCAPE))
                backPressed();
        }
    }
    return true;
}

void ShopState::handleXboxEvents(int player,XboxController* state)
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
		else if(state->dpadRight || state->leftStick.x > 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                rightPressed();
            }
            prevTime = clock.getCurrentTime();
        }
		else if(state->dpadLeft || state->leftStick.x < 0)
        {
            if(clock.getDeltaTime(prevTime) > WAIT_TIME || !buttonPressed)
            {
                if(!buttonPressed)
                    buttonPressed = true;
                leftPressed();
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


void ShopState::upPressed()
{
	if(!inSubmenu)
	{
		if(currentSelectedCategory == 0)
		{
			//Play not possible sound
		}
		else
		{
			currentSelectedCategory--;
			soundEngine->playSound(4,7); 
		}
	}
}

void ShopState::downPressed()
{
	if(!inSubmenu)
	{
		if(currentSelectedCategory == MAX_CATEGORY_SELECTED -1)
		{
			//Play not possible sound
		}
		else
		{
			currentSelectedCategory++;
			soundEngine->playSound(4,7); 
		}
	}
}

void ShopState::rightPressed()
{
	if(inSubmenu)
	{
		if(currentSelectedItem == MAX_ITEM_SELECTED)
		{
			//Play not possible sound
		}
		else
		{
			currentSelectedItem++;
			soundEngine->playSound(4,7); 
		}
	}
}

void ShopState::leftPressed()
{
    if(inSubmenu)
	{
		if(currentSelectedItem == 0)
		{
			//Play not possible sound
		}
		else
		{
			currentSelectedItem--;
			soundEngine->playSound(4,7); 
		}
	}
}

void ShopState::selectPressed()
{
    soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress

	if(!inSubmenu)
	{
		switch(currentSelectedCategory)
		{
		case 0:
			printf("Ships\n");
			inSubmenu = true;
			//Ships
			//MAX_ITEMS_SELECTED = # of ships -1
			break;
		case 1:
			printf("Upgrades\n");
			inSubmenu = true;
			//Upgrades
			//MAX_ITEMS_SELECTED = # of upgrades -1
			break;
		case 2:
			printf("Paint\n");
			inSubmenu = true;
			//Paint
			//MAX_ITEMS_SELECTED = # of paint styles -1
			break;
		case 3:
			//Done
			printf("Done\n");
			renderingEngine->startTransition(RenderingEngine::FADE_OUT);
			lockControls = true;
			break;
		}
	}
	else  // In a sub menu
	{
		// The meat and potatoes of this screen
	}
   
}

void ShopState::backPressed()
{
	if(!inSubmenu)
	{
		lockControls = true;
		renderingEngine->startTransition(RenderingEngine::FADE_OUT);
	}
	else
	{
		// Play some sort of cancel noise
		inSubmenu = false;
	}
}
ShopState* ShopState::getInstance()
{    
     printf("Shop state\n");
    static ShopState ShopState;
    ShopState.changeState(SHOP);
    ShopState.initialize();
    return &ShopState;
}
