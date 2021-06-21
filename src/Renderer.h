#pragma once

#include <SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Camera;
class SpriteComponent;
class Texture;
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

    void DrawTexture(SDL_Texture* texture, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
    Texture* GetTexture(const std::string& fileName);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    void AddParticles(ParticleEmitterComponent* emitter);
    void RemoveParticles(ParticleEmitterComponent* emitter);

    Camera* GetCamera() const { return camera; }
private:
    friend class SpriteComponent;
    friend class ParticleEmitterComponent;
    friend class TileMapRenderer;
    friend class DebugRenderer;
    
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;
    Camera* camera;
};
