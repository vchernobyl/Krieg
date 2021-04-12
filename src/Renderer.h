#pragma once

#include <vector>

class Renderer {
public:
    Renderer(class Game*);
    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();
    void Begin();
    void Draw();
    void End();
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    class SDL_Renderer* GetSDLRenderer() const { return renderer; }
    class Camera* GetCamera() const { return camera; }
private:
    class SDL_Window* window;
    class SDL_Renderer* renderer;
    std::vector<class SpriteComponent*> sprites;
    class Game* game;
    class Camera* camera;
    class TileMap* map;
};
