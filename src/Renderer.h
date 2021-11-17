#pragma once

#include "Math.h"
#include "SpriteBatch.h"

#include <SDL/SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Texture;
class SpriteComponent;
class ParticleComponent;
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

    void AddParticles(ParticleComponent* emitter);
    void RemoveParticles(ParticleComponent* emitter);

    void SetViewMatrix(const Matrix4& view) { this->view = view; }
    void SetUIViewMatrix(const Matrix4& uiView) { this->uiView = uiView; }

    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }

private:
    bool LoadShaders();
    
    SDL_Window* window;
    SDL_GLContext context;

    SpriteBatch spriteBatch;
    SpriteBatch uiSpriteBatch;

    Shader* textureShader;
    Shader* uiShader;
    
    Matrix4 uiView;
    Matrix4 view;

    std::vector<SpriteComponent*> sprites;
    std::vector<ParticleComponent*> particles;

    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    int screenWidth;
    int screenHeight;

    // Game specific, remove later.
    class DebugUI* debugUI;
    class Font* font;
};
