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

    initializeInventory();

    //ssi = new ssi???
    ssi.di.clear();
    //ssi.playerName;       //Rendering will use Profile:playerInShop to display this info
    //ssi.playerObs;

    ssi.inSubmenu = false;

    ssi.selectedMenuIndex = currentSelectedCategory;
    ssi.selectedItemIndex = currentSelectedItem;
    //end ssi initialization

    //texture 42 is mechanic =)
    mechanicGirl = new DynamicImage(-125,400,0,20,20,42,1);   //will probably be overwritten in reset(), so change the values there
    painterGirl = new DynamicImage(-50,50,0,20,20,43,0);

	enterMechanic();
}


void ShopState::initializeInventory()
{
    availableShips.clear();
    availablePaints.clear();
    availableUpgrades.clear();

    shopItem* newItem;

    //Buyable Ship Models
    newItem = new shopItem;
        newItem->itemIndex = 1;      //saruk
        newItem->price = 0;
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 11;      //Claymore
        newItem->price = 100000;
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 14;      //Boxer
        newItem->price = 100000;
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 12;      //Nogard
        newItem->price = 500000;
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 15;      //MiniMothership
        newItem->price = 1000000;
        availableShips.push_back(newItem);



    //TODO: Buyable Upgrades (Index is not bound to anything)
    newItem = new shopItem;
        newItem->itemIndex = 0;      //TODO: SHUNTING
        newItem->price = 1000000;
        availableUpgrades.push_back(newItem);


}


void ShopState::initializePaintJob(int shipModel)
{
    availablePaints.clear();

    shopItem* newItem;

    switch (shipModel)
    {
        case 1:     //Saruk
            newItem = new shopItem;
                newItem->itemIndex = 3;      //Standard
                newItem->price = 0;
                availablePaints.push_back(newItem);
            break;

        case 11:     //Claymore
            newItem = new shopItem;
                newItem->itemIndex = 52;      //Standard
                newItem->price = 0;
                availablePaints.push_back(newItem);
            break;

        case 14:     //Boxer
            //newItem = new shopItem;
            //    newItem->itemIndex = 3;      //Standard
            //    newItem->price = 0;
             //   availablePaints.push_back(newItem);
            break;

        case 12:     //Nogard
            newItem = new shopItem;
                newItem->itemIndex = 50;      //Standard
                newItem->price = 0;
                availablePaints.push_back(newItem);
            break;

        case 15:     //MiniMothership
            newItem = new shopItem;
                newItem->itemIndex = 27;      //Standard
                newItem->price = 0;
                availablePaints.push_back(newItem);
            break;

        default:     //in case

            break;
    }

    //Add some generic Paints
    newItem = new shopItem;
                newItem->itemIndex = 0;      //Test Texture
                newItem->price = 1000;
                availablePaints.push_back(newItem);

    newItem = new shopItem;
                newItem->itemIndex = 51;      //Black
                newItem->price = 5000;
                availablePaints.push_back(newItem);
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

        if(state->dpadUp || state->leftStick.y >  0)
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
		if(state->dpadRight || state->leftStick.x > 0)
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
            ssi.selectedMenuIndex = currentSelectedCategory;
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
            ssi.selectedMenuIndex = currentSelectedCategory;
		}
	}
}

void ShopState::rightPressed()
{
	if(inSubmenu)
	{
		if(currentSelectedItem == MAX_ITEM_SELECTED - 1)
		{
			//Play not possible sound
		}
		else
		{
			currentSelectedItem++;
			soundEngine->playSound(4,7);
            if (currentSelectedItem < MAX_ITEM_SELECTED)
            {
                switch (currentSelectedCategory)
                {
                case 0:     //Ship
                    ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex;  initializePaintJob(ssi.selectedItemIndex);ssi.newShipTexture=availablePaints[0]->itemIndex;break;
                case 1:     //upgrades
                    ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;break;
                case 2:     //Paint
                    ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;break;
                }
            }

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

            if (currentSelectedItem < MAX_ITEM_SELECTED)
            {
                switch (currentSelectedCategory)
                {
                case 0:     //Ship
                    ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex;  initializePaintJob(ssi.selectedItemIndex);ssi.newShipTexture=availablePaints[0]->itemIndex;break;
                case 1:     //upgrades
                    ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;break;
                case 2:     //Paint
                    ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;break;
                }
            }

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
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex; initializePaintJob(ssi.selectedItemIndex);ssi.newShipTexture=availablePaints[0]->itemIndex;
            MAX_ITEM_SELECTED = availableShips.size();
            break;
			//Ships
			//MAX_ITEMS_SELECTED = # of ships -1
			break;
		case 1:
			printf("Upgrades\n");
			inSubmenu = true;
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            if ((unsigned) currentSelectedItem > availableUpgrades.size() - 1){printf("ShopState: HEY! No items in Upgrade!!!\n");}
            else
                ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;
            MAX_ITEM_SELECTED = availableUpgrades.size();
			//Upgrades
			//MAX_ITEMS_SELECTED = # of upgrades -1
			break;
		case 2:
			printf("Paint\n");
			inSubmenu = true;
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            initializePaintJob(gameVariables->playerInShop->data.carModel);
            ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;
            MAX_ITEM_SELECTED = availablePaints.size();
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
        switch(currentSelectedCategory)
		{
		case 0:
			printf("Buy selected Ship\n");
            //if hasenough money, buy item, and go back to root
			break;
		case 1:
			printf("Buy selected Upgrades\n");
			break;
		case 2:
			printf("Buy selected Paint\n");
			break;
		}
	}


    ssi.inSubmenu = inSubmenu;
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
    ssi.inSubmenu = inSubmenu;
}
ShopState* ShopState::getInstance()
{    
     printf("Shop state\n");
    static ShopState ShopState;
    ShopState.changeState(SHOP);
    ShopState.initialize();
    return &ShopState;
}
