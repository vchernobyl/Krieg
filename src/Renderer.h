#pragma once

#include <SDL.h>
#include <vector>

class Game;
class Camera;
class SpriteComponent;

class Renderer {
public:
    Renderer(Game*);
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void Begin();
    void Draw();
    void DrawTexture(SDL_Texture* texture, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void End();
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    SDL_Renderer* GetSDLRenderer() const { return renderer; }
    Camera* GetCamera() const { return camera; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SpriteComponent*> sprites;
    Game* game;
    Camera* camera;
};
