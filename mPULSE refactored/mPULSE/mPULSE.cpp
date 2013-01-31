#include <SDL.h>
#include <SDL_opengl.h>
#include "GameStates\Game.h"
#include "Util\Clock.h"
#include "Input\XboxController.h"

bool init();

SDL_Surface* screen = NULL;
bool gameRunning = true;
const int MAX_PLAYERS = 4;
int numPlayers = 0;
int frameRate = 60;
Game game;
XboxController* players[MAX_PLAYERS];
Clock gameClock(frameRate);
float deltaTime = 0;
SDL_Event KeyboardMouseState;    
XINPUT_STATE XboxState;
 
int main(int argc, char *argv[])
{
    if (!init())
        gameRunning = false;

    while(gameRunning)
    {
        deltaTime = gameClock.getDeltaTime();

        //Handle window events
        while(SDL_PollEvent(&KeyboardMouseState))
            gameRunning = game.handleKeyboardMouseEvents(KeyboardMouseState);

        //Handle xbox events
        for(int player=0;player<numPlayers;player++)
        {
            if(players[player]->getState(&XboxState))
                game.handleXboxEvents(player,&XboxState);
        }

        //physics simulations
        game.update(deltaTime);

        //openGL calls
        game.render();  

        //Display to screen
        SDL_GL_SwapBuffers();
        printf("FPS: %f\n",(1000/deltaTime));
    }

    SDL_Quit();
    return 0;
}


bool init()
{
    for(int i=0;i<MAX_PLAYERS;i++)
    {
        players[i] = new XboxController(i);
        if (players[i]->isConnected())
            numPlayers++;
    }

	//Create Main Window	
	if ((screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
		printf("Failed to initize graphics\n");
		return false;	
	}
    SDL_WM_SetCaption("mPULSE","mPULSE");

    return true;
}