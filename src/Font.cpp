#include "Font.h"
#include "Game.h"
#include "Texture.h"

Font::Font() {
}

Font::~Font() {
}

bool Font::Load(const std::string& fileName) {
    // Supported font sizes.
    std::vector<int> fontSizes = {
        8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28,
        30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 52, 56,
        60, 64, 68, 72
    };

    // Call TTF_OpenFont once per every font size.
    for (const auto& size : fontSizes) {
        TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
        if (font == nullptr) {
            SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
            return false;
        }
        fontData.emplace(size, font);
    }

    return true;
}

void Font::Unload() {
    for (const auto& font : fontData) {
        TTF_CloseFont(font.second);
    }
}

Texture* Font::RenderText(const std::string& text, const Vector4& color, int pointSize) {
    Texture* texture = nullptr;

    SDL_Color sdlColor;
    sdlColor.r = static_cast<Uint8>(color.x * 255);
    sdlColor.g = static_cast<Uint8>(color.y * 255);
    sdlColor.b = static_cast<Uint8>(color.z * 255);
    sdlColor.a = static_cast<Uint8>(color.w * 255);

    // Find the font data for the given point size.
    auto iter = fontData.find(pointSize);
    if (iter != fontData.end()) {
        TTF_Font* font = iter->second;
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
        if (surface != nullptr) {
            texture = new Texture();
            texture->CreateFromSurface(surface);
            SDL_FreeSurface(surface);
        }
    } else {
        SDL_Log("Point size %d is not supported", pointSize);
    }

    return texture;
}
