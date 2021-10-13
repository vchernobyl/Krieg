#pragma once

#include <SDL/SDL.h>
#include <vector>

class Actor;
class Renderer;
class PhysicsWorld;
class AudioSystem;
class InputSystem;
class TileMapRenderer;
class TileMap;

// TODO: Extract game interface to hold all game generic functionality.
class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    Renderer* GetRenderer() const { return renderer; }
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }
    AudioSystem* GetAudioSystem() { return audioSystem; }

    // TODO: Game specific, remove later.
    void AddAsteroid(class Asteroid* asteroid);
    void RemoveAsteroid(class Asteroid* asteroid);
    
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

    // TODO: Game specific, remove it all later.
    TileMapRenderer* tileMapRenderer;
    std::vector<class Asteroid*> asteroids;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;
};
