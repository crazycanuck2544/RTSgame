
#include "Common.h"
#include "GameObject.h"
#include "MemoryTracker.h"
#include "Game.h"
#include "Console.h"

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char *argv[])
{

#ifdef DEBUG

    init_console();

#endif

    INF("Main", "Starting Up");

    gpMemoryTracker = new MemoryTracker();

    Game *game = New Game();
    game->init();

    INF("Main", "Starting Game Loop");

    game->start();

    INF("Main", "Shutting Down");

    delete game;

#ifdef DEBUG

    if (gpMemoryTracker->numAllocations() > 0)
    {
        gpMemoryTracker->printAllocations();
        pause();
    }

    delete gpMemoryTracker;
    gpMemoryTracker = nullptr;

#endif

    return 0;

}