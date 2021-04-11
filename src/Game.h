#pragma once

#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    SDL_Texture* GetTexture(const std::string& filename);
    class Renderer* GetRenderer() const { return renderer; }
    class Camera* GetCamera() const { return camera; }
    class PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }
private:
    void ProcessInput();
    void UpdateGame();
    void DrawGame();
    void LoadData();
    void UnloadData();

    std::unordered_map<std::string, SDL_Texture*> textures;
    std::vector<class Actor*> actors;
    std::vector<class Actor*> pendingActors;
    std::vector<class SpriteComponent*> sprites;

    class Renderer* renderer;
    class InputSystem* inputSystem;
    class PhysicsWorld* physicsWorld;
    class Camera* camera;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;
};
