#pragma once

// TODO: Remove this header once SpriteEffect enum is moved to the texture.
#include "SpriteComponent.h"

#include "Math.h"

#include <SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Texture;
class Vector2;
class Rectangle;
class SpriteComponent;
class ParticleEmitterComponent;

class Renderer {
public:
    Renderer(Game*);
    bool Initialize(int windowWidth, int windowHeight);
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
    
    void SetView(const Vector2& view) { cameraView = view; }
    const Vector2& GetView() const { return cameraView; }
    const Vector2& GetWindowSize() const { return windowSize; }
    
private:
    friend class DebugRenderer;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext context;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    Vector2 cameraView;
    Vector2 windowSize;
};
