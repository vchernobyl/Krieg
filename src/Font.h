#pragma once

#include "Math.h"
#include <string>
#include <map>

struct Character {
    unsigned int textureID;
    Vector2 size;
    Vector2 bearing;
    unsigned int advance;
};

class Font {
public:
    Font();
    ~Font();
    bool Load(const std::string& fileName);
    void Unload();
private:
    std::map<char, Character> characters;
};
