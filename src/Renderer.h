#pragma once

#include <SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Camera;
class SpriteComponent;
class Texture;
class ParticleSystem;

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

    void AddParticles(ParticleSystem* particles);
    void RemoveParticles(ParticleSystem* particles);    
    
    SDL_Renderer* GetSDLRenderer() const { return renderer; }
    Camera* GetCamera() const { return camera; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleSystem*> particles;
    std::unordered_map<std::string, Texture*> textures;

    Game* game;
    Camera* camera;
};
