#pragma once

#include "SDL.h"
#include <vector>

class Renderer {
public:
    Renderer(class Game*);
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void Begin();
    void Draw();
    void DrawTexture(SDL_Texture* texture, SDL_Rect* dst, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void End();
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    SDL_Renderer* GetSDLRenderer() const { return renderer; }
    class Camera* GetCamera() const { return camera; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<class SpriteComponent*> sprites;
    class Game* game;
    class Camera* camera;
    class TileMap* map;
};
