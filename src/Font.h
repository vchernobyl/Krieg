#pragma once

#include "Math.h"
#include <SDL/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <cassert>

class Font {
public:
    Font();
    ~Font();
    bool Load(const std::string& fileName);
    void Unload();

    // TODO: Look at the API examples from MonoGame or LibGDX.
    // This would be a LibGDX version.
    // What we could do is that we create a map of text-to-texture map.
    // Whenever font is requested to draw a text of a certain font size, we first look it up
    // in this map and use it if it already exists. Otherwise we create and store the texture for
    // future use. Whenever the font is unloaded, we clear the maps and texture pointers.
    void Draw(class SpriteBatch& spriteBatch, const std::string& text, const Vector2& position) {
        assert(false); // Not implemented.
    }

    class Texture* RenderText(const std::string& text,
                              const Vector4& color = Color::White,
                              int pointSize = 30);
private:
    std::unordered_map<int, TTF_Font*> fontData; // TODO: Forward declare TTF_Font.
};
