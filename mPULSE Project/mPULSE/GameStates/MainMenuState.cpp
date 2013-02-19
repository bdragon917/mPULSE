#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
    changeState(MAIN_MENU);    
    //entities.cars.push_back(new Entity);
    physicsEngine = PhysicsEngine::getInstance();
    //physicsEngine->setupPlayScene(&entities.cars);
    renderingEngine = RenderingEngine::getInstance();
	//renderingEngine->initializeGL();
    renderingEngine->createLight_MainMenu();

}

void MainMenuState::update(float dt)
{    

}

void MainMenuState::render()
{   
    //int curMenuButton = 0;
    //bool clicked = 0;

	if (renderingEngine->drawMainMenuScreen(curSelected, 0) == 1)
    {
        switch (curSelected)
        {
        case 0:
            changeState(PLAY);
            break;
        case 1:
            changeState(MAIN_MENU); 
            break;
        case 2:
            changeState(MAIN_MENU); 
            break;
        case 3:
            changeState(MAIN_MENU); 
            break;
        case 4:
            changeState(MAIN_MENU); 
            break;
        }
    }
}


bool MainMenuState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    int MaxSelected = 5;


    //Non-Console
        if (KeyboardMouseEvents.type == SDL_KEYDOWN)
         {
            SDLKey keyPressed = KeyboardMouseEvents.key.keysym.sym;

            if ((keyPressed == SDLK_LEFT) || (keyPressed == SDLK_a))
            {
                curSelected = curSelected - 1;
                if (curSelected < 0){curSelected = MaxSelected;}
                
            }
            else if ((keyPressed == SDLK_RIGHT) || (keyPressed == SDLK_d))
            {
                curSelected = curSelected + 1;
                if (curSelected > MaxSelected){curSelected = 0;}
            }
            else if ((keyPressed == SDLK_RETURN) || (keyPressed == SDLK_SPACE))
            {
                renderingEngine->startFadeOut();
            }

                

        }


    return true;
}

void MainMenuState::handleXboxEvents(int player,XboxController* state)
{

}

MainMenuState* MainMenuState::getInstance()
{    
     printf("main menu state\n");
    static MainMenuState MainMenuState;
    MainMenuState.changeState(MAIN_MENU);
    return &MainMenuState;
}