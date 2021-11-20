#include "Font.h"
#include "Game.h"
#include "Texture.h"
#include "Shader.h"
#include "Math.h"
#include "Renderer.h"
#include "Camera.h"
#include "SpriteBatch.h"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// TODO: Assert GL_CALL.
Font::Font(Game* game) : game(game) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Font::~Font() {
}

bool Font::Load(const std::string& fileName, unsigned int fontSize) {
    // TODO: Move this out to the renderer or whatever.
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        SDL_Log("Unable to initialize FreeType");
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, fileName.c_str(), 0, &face)) {
        SDL_Log("Unable to load font: %s", fileName.c_str());
        return false;
    }

    // `0` let's width to be dynamically calculated based on given height.
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char ch = 0; ch < 128; ch++) {
        if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
            SDL_Log("Failed to load a glyph: %s", ch);
            continue;
        }

        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            textureID,
            Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        characters.emplace(ch, character);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void Font::Unload() {
}

void Font::Draw(SpriteBatch& spriteBatch, const std::string& text,
                const Vector2& position, float scale, int drawOrder, const Vector4& color) {
    auto cursor = position.x;
    for (auto ch = text.begin(); ch != text.end(); ch++) {
        Character character = characters[*ch];

        const float pixelsPerUnit = 64.0f;

        float xPos = (cursor + (character.bearing.x / pixelsPerUnit) * scale);
        float yPos = (position.y - ((character.size.y - character.bearing.y) / pixelsPerUnit) * scale);

        float w = character.size.x * scale / pixelsPerUnit;
        float h = character.size.y * scale / pixelsPerUnit;

        spriteBatch.Draw(Vector4(xPos, yPos, w, h), Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                         character.textureID, drawOrder, color);

        cursor += (character.advance >> 6) / pixelsPerUnit * scale;
    }
}
