#include "Game.h"
#include <iostream>

int main(int argc, char** argv) {
    Game game;
    if (game.Initialize()) {
	game.RunLoop();
    }
    game.Shutdown();
    std::cin.get();
    return 0;
}
