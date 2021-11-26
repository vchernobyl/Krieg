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
class UILayer;

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
    
    const std::vector<UILayer*>& GetUIStack() { return uiStack; }
    void PushUI(UILayer* layer);

private:
    void ProcessInput();
    void UpdateGame();
    void DrawGame();
    void LoadData();
    void UnloadData();

    std::vector<Actor*> actors;
    std::vector<Actor*> pendingActors;
    std::vector<UILayer*> uiStack;

    std::unordered_map<std::string, Font*> fonts;

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
