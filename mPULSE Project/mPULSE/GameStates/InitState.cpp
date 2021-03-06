#include <GameStates/InitState.h>

InitState::InitState()
{
    stateType = INIT;
    quit = false;
    renderingEngine = RenderingEngine::getInstance();
	soundEngine = SoundEngine::getInstance();
    //renderingEngine->initializeGL();          //should be initalized when RenderingEngine was created
	soundEngine->initializeSound();
    //soundEngine->playFinalCountDown();
	soundEngine->startMusic(0);
    gameVariables = GameVariables::getInstance();
    gameVariables->initialize(); 
    time = clock.getCurrentTime();
}

void InitState::update(float dt)
{    
    //if((clock.getCurrentTime() - time) > TIMEOUT) //Just testing a timed state transition
        //changeState(PLAY);
        changeState(MAIN_MENU);

}
void InitState::render()
{
    
    //renderingEngine->drawIntro2();
}

bool InitState::handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents)
{
    return true;
}

void InitState::handleXboxEvents(int player,XboxController* state)
{

}

InitState* InitState::getInstance()
{
    printf("init state\n");
    static InitState initState;
    initState.changeState(INIT);
    return &initState;
}
