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
class VertexArray;
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
    
    void SetViewMatrix(const Matrix4& view) { this->view = view; }

private:
    friend class DebugRenderer;

    bool LoadShaders();
    void CreateSpriteVertices();
    
    SDL_Window* window;
    SDL_GLContext context;

    SpriteBatch spriteBatch;
    VertexArray* spriteVertices;
    Shader* spriteShader;
    Shader* textureShader;

    Matrix4 view;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    int screenWidth;
    int screenHeight;
};
