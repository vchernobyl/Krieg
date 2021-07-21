#pragma once

#include "Math.h"
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class Texture {
public:
    int width, height;

    // TODO: Hide this guy.
    SDL_Texture* texture;

    Texture();
    void SetColor(const Vector3& color);
    void SetColor(const Vector4& color);
private:
    friend class Renderer;
    bool Load(const std::string& fileName, SDL_Renderer* renderer);
    void Unload();
};
