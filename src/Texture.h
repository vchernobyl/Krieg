#pragma once

#include <string>

class Texture {
public:
    int width, height;

    Texture();

    bool Load(const std::string& fileName);
    void Unload();
private:
    struct SDL_Texture* texture;
};
