#include "Game.h"

// TODO: This needs to be removed.
// SDL_main initialization is explained here: https://wiki.libsdl.org/SDL_SetMainReady.
// Interestingly, if we set the `/SUBSYSTEM:windows` then the project does not compile, unless
// we remove this line. However, sometimes we do want to keep the console open for debugging
// and logging purposes.
#undef main

int main(int argc, char** argv) {
    Game game;
    if (game.Initialize()) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
