#pragma once

#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class Texture {
public:
    int width, height;
    Texture();
    
private:
    friend class Renderer;
    bool Load(const std::string& fileName, SDL_Renderer* renderer);
    void Unload();
    SDL_Texture* texture;
};
