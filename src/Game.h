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
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    SDL_Texture* GetTexture(const std::string& filename);
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

    SDL_Window* window;
    SDL_Renderer* renderer;

    class DebugRenderer* debugRenderer;
    class InputSystem* inputSystem;
    class PhysicsWorld* physicsWorld;
    class Camera* camera;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;

    class TileMap* map;
};
