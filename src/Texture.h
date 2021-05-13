#pragma once

#include "Math.h"
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class Texture {
public:
    int width, height;
    SDL_Texture* texture;

    Texture();
    void SetColor(const Vector3& color);
private:
    friend class Renderer;
    bool Load(const std::string& fileName, SDL_Renderer* renderer);
    void Unload();
};
