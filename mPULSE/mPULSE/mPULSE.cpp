#define NOMINMAX
#define NO_SDL_GLEXT

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameStates\Game.h"
#include "Util\Clock.h"
#include "Input\XboxController.h"

//Methods
bool init();

//Variables
SDL_Surface* screen = NULL;
const int MAX_PLAYERS = 4;
int numPlayers = 0;
XboxController* players[MAX_PLAYERS];
 
int main(int argc, char *argv[])
{
    Game game;
    SDL_Event KeyboardMouseState;    
    bool gameRunning = true;

    gameRunning = init();
    while(gameRunning)
    {
        //Handle window events
        while(SDL_PollEvent(&KeyboardMouseState))
            gameRunning = game.handleKeyboardMouseEvents(KeyboardMouseState);

        //Handle xbox events
        for(int player=0;player<numPlayers;player++)
        {
            players[player]->update();
            game.handleXboxEvents(player,players[player]);
        }
        
		game.update();  //physics simulations
		game.render();  //openGL calls          

        //Display to screen
        SDL_GL_SwapBuffers();
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
	if ((screen = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
		printf("Failed to initize graphics\n");
		return false;	
	}
    SDL_WM_SetCaption("mPULSE","mPULSE");

    return true;
}