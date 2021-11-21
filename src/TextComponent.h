#pragma once

#include "Component.h"
#include "Math.h"
#include <string>

class TextComponent : public Component {
public:
    TextComponent(class Actor* owner, int drawOrder = 200);
    ~TextComponent();

    void Draw(class SpriteBatch& spriteBatch);
    void SetText(const std::string& text) { this->text = text; }
    void SetFont(class Font* font) { this->font = font; }
    void SetColor(const Vector4& color) { this->color = color; }
private:
    class Font* font = nullptr;
    std::string text;
    Vector4 color = Color::White;
};
