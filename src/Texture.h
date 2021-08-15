#pragma once

#include <string>

class Texture {
public:
    bool Load(const std::string& fileName);
    void Unload();
    void SetActive();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

private:
    unsigned int textureID = 0;
    int width = 0;
    int height = 0;
};
