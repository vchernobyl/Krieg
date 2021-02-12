#pragma once

#include "SDL.h"
#include <vector>
#include <unordered_map>
#include <string>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    SDL_Texture* GetTexture(const std::string& filename);
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    std::unordered_map<std::string, SDL_Texture*> textures;
    std::vector<class Actor*> actors;
    std::vector<class Actor*> pendingActors;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    bool updatingActors;

    Uint32 ticks;
};
