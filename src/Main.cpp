#include "Game.h"
#include "Math.h"
#include <iostream>

int main(int argc, char** argv) {
    Vector2 acc(1, 1);
    acc += Vector2(5, 2) * 10;
    std::cout << "x = " << acc.x << std::endl;
    std::cout << "y = " << acc.y << std::endl;
    std::cin.get();

    Game game;
    if (game.Initialize()) {
	game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
