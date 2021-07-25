#pragma once

#include "SpriteComponent.h"

#include <SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Camera;
class Texture;
class Vector2;
class Rectangle;
class SpriteComponent;
class ParticleEmitterComponent;

class Renderer {
public:
    Renderer(Game*);
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void UnloadData();

    void Begin();
    void Draw();
    void End();

    void DrawTexture(const Texture* texture, const Rectangle& src, const Rectangle& dst,
		     double angle, SpriteEffect effect);

    Texture* GetTexture(const std::string& fileName);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    void AddParticles(ParticleEmitterComponent* emitter);
    void RemoveParticles(ParticleEmitterComponent* emitter);

    Camera* GetCamera() const { return camera; }
private:
    // TODO: Remove these after DrawTexture() is implemented.
    friend class DebugRenderer;
    
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;
    Camera* camera;
};
