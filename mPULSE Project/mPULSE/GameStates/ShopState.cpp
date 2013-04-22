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
	BASE_PICKUP_UPGRADE = 5000;

    buttonPressed = false;
    lockControls = false;
    goBack = false;

    initializeInventory();

    //ssi = new ssi???
    ssi.di.clear();
    ssi.obsCost = 0;
    //ssi.playerName;       //Rendering will use Profile:playerInShop to display this info
    //ssi.playerObs;

    ssi.selectedItemName = "";

    ssi.inSubmenu = false;

    ssi.selectedMenuIndex = currentSelectedCategory;
    ssi.selectedItemIndex = currentSelectedItem;
    //end ssi initialization

    int screen_width = renderingEngine->SCREEN_WIDTH;
    int screen_height = renderingEngine->SCREEN_HEIGHT;


    //texture 42 is mechanic =)
    mechanicGirl = new DynamicImage(-125,400,0,20,20,42,1);   //will probably be overwritten in reset(), so change the values there
    painterGirl = new DynamicImage(-50,50,0,20,20,43,1);
    subMenu = new DynamicImage(screen_width / 2,0,0,screen_width * 4, screen_height, 123 , 1);
    ssi.di.push_back(subMenu);

    soundEngine->playSound(5,(rand() % 5) + 27);    //4 is channel, 7 is index for intro

	enterMechanic();
    enterPainter();
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
        newItem->name = "Saruk";
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 11;      //Claymore
        newItem->price = ((gameVariables->playerInShop->data.shipsOwned[1]) ? 0:60000);
        newItem->name = "Claymore";
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 14;      //Boxer
        newItem->price = ((gameVariables->playerInShop->data.shipsOwned[2]==1) ? 0:100000);
        newItem->name = "Boxer";
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 12;      //Nogard
        newItem->price = ((gameVariables->playerInShop->data.shipsOwned[3]==1) ? 0:150000);
        newItem->name = "Nogard";
        availableShips.push_back(newItem);

    newItem = new shopItem;
        newItem->itemIndex = 15;      //MiniMothership
        newItem->price = ((gameVariables->playerInShop->data.shipsOwned[4]==1) ? 0:200000);
        newItem->name = "M.M.";
        availableShips.push_back(newItem);



    //TODO: Buyable Upgrades (Index is not bound to anything)
    newItem = new shopItem;
        newItem->itemIndex = 30;     //TODO: IMPULSE BATTERY
		newItem->price = ((gameVariables->playerInShop->data.batteryLevel != 0) ? 0:10000);
        newItem->name = "Impluse Battery";
        availableUpgrades.push_back(newItem);

	newItem = new shopItem;
		newItem->itemIndex = 31;		//TODO: STRAFE
		newItem->price = ((gameVariables->playerInShop->data.strafeLevel != 0) ? 0:10000);
        newItem->name = "Strafe Thursters";
		availableUpgrades.push_back(newItem);

	newItem = new shopItem;
		newItem->itemIndex = 32;		//TODO: MISSILE ++
		newItem->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.missileLevel) % (BASE_PICKUP_UPGRADE * 5));
        newItem->name = "Upgrade Missiles";
		availableUpgrades.push_back(newItem);

	newItem = new shopItem;
		newItem->itemIndex = 33;		//TODO: BARRIER ++
		newItem->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.barrierLevel) % (BASE_PICKUP_UPGRADE * 5));
        newItem->name = "Upgrade Barriers";
		availableUpgrades.push_back(newItem);

	newItem = new shopItem;
		newItem->itemIndex = 34;		//TODO: BOOST ++
		newItem->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.boostLevel) % (BASE_PICKUP_UPGRADE * 5));
        newItem->name = "Upgrade Boost";
		availableUpgrades.push_back(newItem);

	newItem = new shopItem;
		newItem->itemIndex = 35;		//TODO: SHIELD ++
		newItem->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.shieldLevel) % (BASE_PICKUP_UPGRADE * 5));
        newItem->name = "Upgrade Shield";
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
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 90;      //Standard
                newItem->price = 1000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 91;      //Standard
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 92;      //Standard
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 93;      //Standard
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 94;      //Standard
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 95;      //Standard
                newItem->price = 4000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 96;      //Standard
                newItem->price = 5000;
                newItem->name = "";
                availablePaints.push_back(newItem);
            break;

        case 11:     //Claymore
            newItem = new shopItem;
                newItem->itemIndex = 52;      //Standard
                newItem->price = 0;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 97;      //Standard
                newItem->price = 1000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 98;      //Standard
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 99;      //Standard
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 100;      //Standard
                newItem->price = 4000;
                newItem->name = "";
                availablePaints.push_back(newItem);
            break;

        case 14:     //Boxer
            newItem = new shopItem;
                newItem->itemIndex = 87;      //Standard
                newItem->price = 0;
                newItem->name = "";
                availablePaints.push_back(newItem);
            newItem = new shopItem;
                newItem->itemIndex = 88;      //Pirate
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 101;      //Pirate
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 102;      //Pirate
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 103;      //Pirate
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 104;      //Pirate
                newItem->price = 4000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 105;      //Pirate
                newItem->price = 5000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 106;      //Pirate
                newItem->price = 5000;
                newItem->name = "";
                availablePaints.push_back(newItem);
            break;

        case 12:     //Nogard
            newItem = new shopItem;
                newItem->itemIndex = 50;      //Standard
                newItem->price = 0;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 107;      //Standard
                newItem->price = 1000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 108;      //Standard
                newItem->price = 1000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 109;      //Standard
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 110;      //Standard
                newItem->price = 3000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 111;      //Standard
                newItem->price = 4000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 112;      //Standard
                newItem->price = 5000;
                newItem->name = "";
                availablePaints.push_back(newItem);
            break;

        case 15:     //MiniMothership
            newItem = new shopItem;
                newItem->itemIndex = 27;      //Standard
                newItem->price = 0;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 113;      //Standard
                newItem->price = 2000;
                newItem->name = "";
                availablePaints.push_back(newItem);

                newItem = new shopItem;
                newItem->itemIndex = 114;      //Standard
                newItem->price = 4000;
                newItem->name = "";
                availablePaints.push_back(newItem);
            break;

        default:     //in case

            break;
    }

    //Add some generic Paints
    newItem = new shopItem;
                newItem->itemIndex = 0;      //Test Texture
                newItem->price = 1000;
                newItem->name = "";
                availablePaints.push_back(newItem);

    newItem = new shopItem;
                newItem->itemIndex = 51;      //Black
                newItem->price = 5000;
                newItem->name = "";
                availablePaints.push_back(newItem);
}


void ShopState::enterMechanic()
{
    mechanicGirl->setLocation(-175,600,0);
    mechanicGirl->setTargetLocation(200,600,0);
    ssi.di.push_back(mechanicGirl);
}

void ShopState::enterPainter()
{
    painterGirl->setLocation(-200,600,0);
    painterGirl->setTargetLocation(-200,600,0);
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
		gameVariables->saveProfiles();
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

		if(!inSubmenu)
		{
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
                    ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex;  
                    ssi.obsCost = availableShips.at(currentSelectedItem)->price;
					initializePaintJob(ssi.selectedItemIndex);
					ssi.newShipTexture=availablePaints[0]->itemIndex;
                    ssi.selectedItemName = availableShips.at(currentSelectedItem)->name;
					break;
                case 1:     //upgrades
                    ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;
                    ssi.obsCost = availableUpgrades.at(currentSelectedItem)->price;
                    ssi.selectedItemName = availableUpgrades.at(currentSelectedItem)->name;
					break;
                case 2:     //Paint
                    ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;
                    ssi.obsCost = availablePaints.at(currentSelectedItem)->price;
                    ssi.selectedItemName = availablePaints.at(currentSelectedItem)->name;
					break;
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
                    ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex;  
                    ssi.obsCost = availableShips.at(currentSelectedItem)->price;
					initializePaintJob(ssi.selectedItemIndex);
					ssi.newShipTexture=availablePaints[0]->itemIndex;
                    ssi.selectedItemName = availableShips.at(currentSelectedItem)->name;
					break;
                case 1:     //upgrades
                    ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;
                    ssi.obsCost = availableUpgrades.at(currentSelectedItem)->price;
                    ssi.selectedItemName = availableUpgrades.at(currentSelectedItem)->name;
					break;
                case 2:     //Paint
                    ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;
                    ssi.obsCost = availablePaints.at(currentSelectedItem)->price;
                    ssi.selectedItemName = availablePaints.at(currentSelectedItem)->name;
					break;
                }
            }

		}
	}
}

void ShopState::selectPressed()
{
	if(!inSubmenu)
	{
        ssi.selectedItemName = "";

        subMenu->setTargetLocation((renderingEngine->SCREEN_WIDTH / 2),(renderingEngine->SCREEN_HEIGHT / 3),0);    //come down to visible
		soundEngine->playSound(3,11);    //3 is channel, 7 is index for MenuPress
		switch(currentSelectedCategory)
		{
		case 0:
			printf("Ships\n");
			inSubmenu = true;
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            ssi.selectedItemIndex = availableShips.at(currentSelectedItem)->itemIndex; 
			initializePaintJob(ssi.selectedItemIndex);
			ssi.newShipTexture=availablePaints[0]->itemIndex;
            ssi.selectedItemName = availableShips.at(currentSelectedItem)->name;
            MAX_ITEM_SELECTED = availableShips.size();
            soundEngine->playSound(5,(rand() % 4) + 41);    //anything you like?
            break;
		case 1:
			printf("Upgrades\n");
			inSubmenu = true;
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            ssi.selectedItemIndex = availableUpgrades.at(currentSelectedItem)->itemIndex;
            ssi.selectedItemName = availableUpgrades.at(currentSelectedItem)->name;
            MAX_ITEM_SELECTED = availableUpgrades.size();
            soundEngine->playSound(5,(rand() % 4) + 41);    //anything you like?
			break;
		case 2:
			printf("Paint\n");
			inSubmenu = true;
            painterGirl->setTargetLocation(200,600,0); //show
            mechanicGirl->setTargetLocation(-200,600,0); //Hide
            ssi.selectedItemIndex = 0;
            currentSelectedItem = 0;
            initializePaintJob(gameVariables->playerInShop->data.carModel);
            ssi.selectedItemIndex = availablePaints.at(currentSelectedItem)->itemIndex;
            ssi.selectedItemName = availablePaints.at(currentSelectedItem)->name;
            MAX_ITEM_SELECTED = availablePaints.size();
            soundEngine->playSound(5,(rand() % 3) + 49);    //anything you like? Painter
			break;
		case 3:
			//Done
			printf("Done\n");
			renderingEngine->startTransition(RenderingEngine::FADE_OUT);
            soundEngine->playSound(5,(rand() % 3) + 38);    //bibi
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
			if(gameVariables->playerInShop->data.Obs >=  availableShips[currentSelectedItem]->price)
			{
				if(gameVariables->playerInShop->data.shipsOwned[currentSelectedItem] == 0)
				{
					printf("ship purchased\n");
					gameVariables->playerInShop->data.Obs -= availableShips[currentSelectedItem]->price;
					gameVariables->playerInShop->data.shipsOwned[currentSelectedItem] = 1;
					gameVariables->playerInShop->data.carModel = availableShips[currentSelectedItem]->itemIndex;
					initializePaintJob(gameVariables->playerInShop->data.carModel);
					gameVariables->playerInShop->data.carTexture = availablePaints[0]->itemIndex;
					availableShips[currentSelectedItem]->price = 0;
                    soundEngine->playSound(5,(rand() % 6) + 41);    //installed
				}
				else
				{
					printf("Already owned\n");
					gameVariables->playerInShop->data.carModel = availableShips[currentSelectedItem]->itemIndex;
					initializePaintJob(gameVariables->playerInShop->data.carModel);
					gameVariables->playerInShop->data.carTexture = availablePaints[0]->itemIndex;
				}
			}
			else
			{
				// Play cannot afford sound
				printf("Cannot afford ship\n");
			}
			break;
		case 1:
			printf("Buy selected Upgrades\n");
			if(gameVariables->playerInShop->data.Obs >=  availableUpgrades[currentSelectedItem]->price)
			{
				switch(currentSelectedItem)
				{
				case 0:		// Battery
					if(gameVariables->playerInShop->data.batteryLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.batteryLevel += 5;
						availableUpgrades[currentSelectedItem]->price = 0;
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;

				case 1:		// Strafing
					if(gameVariables->playerInShop->data.strafeLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.strafeLevel += 5;
						availableUpgrades[currentSelectedItem]->price = 0;
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;

				case 2:		// Missle
					if(gameVariables->playerInShop->data.missileLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.missileLevel++;
						availableUpgrades[currentSelectedItem]->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.missileLevel) % (BASE_PICKUP_UPGRADE * 5));
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;

				case 3:		// Barrier
					if(gameVariables->playerInShop->data.barrierLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.barrierLevel++;
						availableUpgrades[currentSelectedItem]->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.barrierLevel) % (BASE_PICKUP_UPGRADE * 5));
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;

				case 4:		// Boost
					if(gameVariables->playerInShop->data.boostLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.boostLevel++;
						availableUpgrades[currentSelectedItem]->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.boostLevel) % (BASE_PICKUP_UPGRADE * 5));
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;

				case 5:		// Shield
					if(gameVariables->playerInShop->data.shieldLevel < 5)
					{
						// Play purchace sound
						gameVariables->playerInShop->data.Obs -= availableUpgrades[currentSelectedItem]->price;
						gameVariables->playerInShop->data.shieldLevel++;
						availableUpgrades[currentSelectedItem]->price = BASE_PICKUP_UPGRADE + ((BASE_PICKUP_UPGRADE * gameVariables->playerInShop->data.shieldLevel) % (BASE_PICKUP_UPGRADE * 5));
                        soundEngine->playSound(5,(rand() % 6) + 32);    //4 is channel, 7 is index for intro
					}
					break;
				}
			}
			else
			{
				// Play "can't afford" sound
			}
			break;
		case 2:
			if(gameVariables->playerInShop->data.Obs >=  availablePaints[currentSelectedItem]->price)
			{
				printf("paint purchased\n");
				gameVariables->playerInShop->data.Obs -= availablePaints[currentSelectedItem]->price;
				gameVariables->playerInShop->data.carTexture = availablePaints[currentSelectedItem]->itemIndex;
                soundEngine->playSound(5,(rand() % 4) + 45);    //4 is channel, 7 is index for intro
			}
			else
			{
				// Play cannot afford sound
				printf("Cannot afford ship\n");
			}
			break;
		}
	}
    ssi.inSubmenu = inSubmenu;
}

void ShopState::backPressed()
{
    mechanicGirl->setTargetLocation(200,600,0); //show
    painterGirl->setTargetLocation(-200,600,0); //Hide

    ssi.selectedItemName = "";

	if(!inSubmenu)
	{
        soundEngine->playSound(5,(rand() % 3) + 38);    //4 is channel, 7 is index for intro
		lockControls = true;
		renderingEngine->startTransition(RenderingEngine::FADE_OUT);
	}
	else
	{
        subMenu->setTargetLocation(renderingEngine->SCREEN_WIDTH / 2,0,0);    //come up to hide
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
