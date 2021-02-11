#include "Game.h"
#include <iostream>

int main(int argc, char** argv) {
    Game g;
    if (g.Initialize()) {
	std::cout << "Initialized";
	g.RunLoop();
    }
    g.Shutdown();
    return 0;
}
