#include "Font.h"
#include "Game.h"
#include "Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Font::Font() {
}

Font::~Font() {
}

bool Font::Load(const std::string& fileName) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        SDL_Log("Unable to initialize FreeType");
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, fileName.c_str(), 0, &face)) {
        SDL_Log("Unable to load font: %s", fileName);
        return false;
    }
    return true;
}

void Font::Unload() {
}
