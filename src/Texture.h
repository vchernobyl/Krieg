#pragma once

#include "Math.h"
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class Texture {
public:
    Texture();

    Vector2 GetSize() const { return Vector2(width, height); }

    void SetColor(const Vector3& color);
    void SetColor(const Vector4& color);

private:
    friend class Renderer;
    
    bool Load(const std::string& fileName, SDL_Renderer* renderer);
    void Unload();

    SDL_Texture* texture;
    int width, height;
};
