#define NOMINMAX
#define NO_SDL_GLEXT

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameStates\Game.h"
#include "Util\Clock.h"
#include "Input\XboxController.h"

// Methods
SDL_Surface* init();

// Constants
const unsigned MAX_PLAYER_COUNT = 4;
 
int main(int argc, char *argv[])
{   
    // Initializes players according to connected controllers
    unsigned playerCount = 0;
    XboxController* players[MAX_PLAYER_COUNT];
    for(unsigned i = 0; i < MAX_PLAYER_COUNT; ++i)
    {
        players[i] = new XboxController(i);
        if (players[i]->isConnected())
            ++playerCount;
    }

    // Initializes display
    SDL_Surface* screen = init();
    bool gameRunning = (screen != NULL);
    Game game;
    SDL_Event KeyboardMouseState;

    // Main game loop
    while(gameRunning)
    {
        //Handle window events
        while(SDL_PollEvent(&KeyboardMouseState))
            gameRunning = game.handleKeyboardMouseEvents(KeyboardMouseState);

        //Handle xbox events
        for (unsigned player = 0; player < playerCount; ++player)
        {
            players[player]->update();
            game.handleXboxEvents(player,players[player]);
        }
        
		game.update();  //physics simulations
		game.render();  //openGL calls          

        //Display to screen
        SDL_GL_SwapBuffers();
	}

    // Cleanup
    SDL_Quit();
    for (unsigned i = 0; i < MAX_PLAYER_COUNT; ++i)
        delete players[i];
    return 0;
}


SDL_Surface* init()
{
    SDL_Surface* screen = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );

	//Initalization for motion blur
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	//Create Main Window	
	if ((screen = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
		printf("Failed to initize graphics\n");
		return false;	
	}

    SDL_WM_SetCaption("mPULSE","mPULSE");

    return screen;
}