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
class VertexArray;
class Shader;

class Renderer {
public:
    Renderer(Game*);

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

    VertexArray* spriteVertices;
    Shader* spriteShader;

    Matrix4 view;
    Matrix4 projection;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleEmitterComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    int screenWidth;
    int screenHeight;
};
