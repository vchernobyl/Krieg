#pragma once

#include "Math.h"
#include "SpriteBatch.h"

#include <SDL/SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Texture;
class SpriteComponent;
class ParticleEmitterComponent;
class Shader;

class Renderer {
public:
    Renderer(Game* game);

    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void UnloadData();
    void Draw();
    Texture* GetTexture(const std::string& fileName);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    void AddParticles(ParticleEmitterComponent* emitter);
    void RemoveParticles(ParticleEmitterComponent* emitter);

    // Kinda feels like this should be in the camera class.
    Vector2 ScreenToWorld(Vector2 screenCoords);

    void SetViewMatrix(const Matrix4& view) { this->view = view; }
    const Matrix4& GetViewMatrix() const { return view; }

    void SetScale(float scale) { this->scale = scale; }
    float GetScale() const { return scale; }

    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }

private:
    bool LoadShaders();
    
    SDL_Window* window;
    SDL_GLContext context;

    SpriteBatch spriteBatch;
    Shader* textureShader;

    Matrix4 view;
    float scale = 64.0;
    float rotation = 0.0f;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    int screenWidth;
    int screenHeight;
};
