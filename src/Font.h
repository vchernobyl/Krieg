#pragma once

#include "Math.h"
#include <string>
#include <map>

struct Character {
    unsigned int textureID;
    Vector2 size;
    Vector2 bearing;
    signed long advance;
};

class Font {
public:
    Font(class Game* game);
    ~Font();
    bool Load(const std::string& fileName, unsigned int fontSize = 48);
    void Unload();
    void RenderText(const std::string& text, float x, float y, float scale, const Vector4& color);
private:
    std::map<char, Character> characters;
    unsigned int VAO, VBO;
    class Shader* shader;
};
