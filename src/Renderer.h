#pragma once

#include <vector>

class Renderer {
public:
    Renderer(class Game*);
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void Draw();
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    class SDL_Renderer* GetSDLRenderer() const { return renderer; }
private:
    class SDL_Window* window;
    class SDL_Renderer* renderer;
    class DebugRenderer* debugRenderer;
    std::vector<class SpriteComponent*> sprites;
    class Game* game;
    class Camera* camera;
    class TileMap* map;
};
