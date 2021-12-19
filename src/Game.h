#pragma once

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
class UIScreen;

class Game {
public:
    Game();

    void Run();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    Camera* GetMainCamera() { return mainCamera; }
    Font* GetFont(const std::string& fileName, int fontSize = 48);
    Actor* GetActorByTag(const std::string& tag);
    Renderer* GetRenderer() const { return renderer; }
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }
    AudioSystem* GetAudioSystem() { return audioSystem; }
    unsigned long GetTicks() const { return ticks; }
    float GetDeltaTime() const { return deltaTime; }
    
    const std::vector<UIScreen*>& GetUIStack() { return uiStack; }
    void PushUI(UIScreen* ui);

protected:
    virtual void LoadData();
    virtual void UnloadData();

private:
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void ProcessInput();
    void UpdateGame();
    void DrawGame();

    std::vector<Actor*> actors;
    std::vector<Actor*> pendingActors;
    std::vector<UIScreen*> uiStack;

    std::unordered_map<std::string, Font*> fonts;

    Renderer* renderer;
    InputSystem* inputSystem;
    AudioSystem* audioSystem;
    PhysicsWorld* physicsWorld;

    Camera* mainCamera;
    Camera* uiCamera;

    bool isRunning;
    bool updatingActors;

    unsigned long ticks;
    float deltaTime;
};
