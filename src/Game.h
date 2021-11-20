#pragma once

#include <SDL/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>

class Actor;
class Renderer;
class PhysicsWorld;
class AudioSystem;
class InputSystem;
class Font;
class Camera;

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    Camera* GetMainCamera() { return mainCamera; }
    Font* GetFont(const std::string& fileName);
    Actor* GetActorByTag(const std::string& tag);
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

    std::unordered_map<std::string, Font*> fonts;
    std::unordered_map<std::string, std::string> text;

    Renderer* renderer;
    InputSystem* inputSystem;
    AudioSystem* audioSystem;
    PhysicsWorld* physicsWorld;

    Camera* mainCamera;
    Camera* uiCamera;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;

    // TODO: Game specific, remove it all later.
    std::vector<class Asteroid*> asteroids;
};
