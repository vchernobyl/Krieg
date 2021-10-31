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
class TileMapRenderer;
class TileMap;

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    class Font* GetFont(const std::string& fileName);
    const std::string& GetText(const std::string& key);
    
    const std::vector<class UIScreen*>& GetUIStack() { return uiStack; }
    void PushUI(class UIScreen* screen);

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
    std::vector<class UIScreen*> uiStack;

    std::unordered_map<std::string, class Font*> fonts;
    std::unordered_map<std::string, std::string> text;

    Renderer* renderer;
    InputSystem* inputSystem;
    AudioSystem* audioSystem;
    PhysicsWorld* physicsWorld;

    // TODO: Game specific, remove it all later.
    std::vector<class Asteroid*> asteroids;

    bool isRunning;
    bool updatingActors;
    Uint32 ticks;
};
