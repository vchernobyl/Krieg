#pragma once

#include "Math.h"
#include <string>
#include <map>

class Font {
public:
    Font(class Game* game);
    ~Font();
    bool Load(const std::string& fileName, unsigned int fontSize = 48);
    void Unload();
    
    // TODO: Add draw order.
    void Draw(class SpriteBatch& spriteBatch, const std::string& text,
              const Vector2& position, float scale = 1.0f, int drawOrder = 1,
              const Vector4& color = Color::White);
private:
    struct Character {
        unsigned int textureID;
        Vector2 size;
        Vector2 bearing;
        signed long advance;
    };

    std::map<char, Character> characters;
    unsigned int VAO, VBO;

    class Shader* shader;
    class Game* game;
};
