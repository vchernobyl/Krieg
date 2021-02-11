#pragma once

#include "SDL.h"
#include <vector>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    std::vector<class Actor*> actors;
    std::vector<class Actor*> pendingActors;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    bool updatingActors;

    Uint32 ticks;
};
