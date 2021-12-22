#pragma once

#include "Maths.h"
#include "SpriteBatch.h"
#include "Shader.h"

#include <SDL/SDL.h>
#include <vector>
#include <unordered_map>

class Game;
class Texture;
class SpriteComponent;
class ParticleComponent;
class DrawableComponent;
class TextComponent;
class Shader;

class Renderer {
public:
    Renderer(Game* game);

    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void UnloadContent();
    void Draw();

    Texture* GetTexture(const std::string& fileName);

    void AddDrawable(DrawableComponent* drawable);
    void RemoveDrawable(DrawableComponent* drawable);

    void SetViewMatrix(const Matrix4& view) { this->view = view; }
    void SetUIViewMatrix(const Matrix4& uiView) { this->uiView = uiView; }

    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }

    void SetClearColor(const Vector4& color) { this->clearColor = color; }

private:
    bool LoadShaders();
    
    SDL_Window* window;
    SDL_GLContext context;

    SpriteBatch spriteBatch;
    SpriteBatch uiSpriteBatch;

    Shader textShader;
    Matrix4 uiView;
    Matrix4 view;

    Vector4 clearColor = Color::Black;

    std::vector<DrawableComponent*> drawables;
    std::unordered_map<std::string, Texture*> textures;

    Game* game;

    int screenWidth;
    int screenHeight;
};
