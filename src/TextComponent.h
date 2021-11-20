#pragma once

#include "Component.h"
#include <string>

class TextComponent : public Component {
public:
    TextComponent(class Actor* owner, int drawOrder = 200);
    ~TextComponent();

    void Draw(class SpriteBatch& spriteBatch);
    void SetText(const std::string& text) { this->text = text; }
    void SetFont(class Font* font) { this->font = font; }
private:
    class Font* font;
    std::string text;
};
