#pragma once

#include <SDL.h>
#include <vector>

class Actor;
class Renderer;
class PhysicsWorld;
class AudioSystem;
class InputSystem;
class TileMapRenderer;
class TileMap;

class Game {
public:
    static constexpr float WorldToBox = 1.0f / 32.0f;
    static constexpr float BoxToWorld = 1.0f / WorldToBox;

    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    Renderer* GetRenderer() const { return renderer; }
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }
    AudioSystem* GetAudioSystem() { return audioSystem; }
private:
    void ProcessInput();
    void UpdateGame();
    void DrawGame();
    void LoadData();
    void UnloadData();

    std::vector<Actor*> actors;
    std::vector<Actor*> pendingActors;

    Renderer* renderer;
    InputSystem* inputSystem;
    AudioSystem* audioSystem;
    PhysicsWorld* physicsWorld;

    // Game specific - will be in a Scene later on
    TileMapRenderer* tileMapRenderer;
    TileMap* tileMap;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;
};
