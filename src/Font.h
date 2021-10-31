#pragma once

#include "Math.h"
#include <SDL/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Font {
public:
    Font(class Game* game);
    ~Font();
    bool Load(const std::string& fileName);
    void Unload();
    class Texture* RenderText(const std::string& textKey,
			      const Vector4& color = Color::White,
			      int pointSize = 30);
private:
    std::unordered_map<int, TTF_Font*> fontData; // TODO: Forward declare TTF_Font.
    class Game* game;
};
