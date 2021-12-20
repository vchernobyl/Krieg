#pragma once

#include "Component.h"
#include "Maths.h"

class SpriteComponent : public DrawableComponent {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);

    void Draw(class SpriteBatch& spriteBatch) override;
    void SetTexture(class Texture* texture);
    void SetColor(const Vector4& color) { this->color = color; }
    const Vector4& GetColor() const { return color; }

    int GetTextureWidth() const { return textureWidth; }
    int GetTextureHeight() const { return textureHeight; }
    Vector2 GetSize() const { return Vector2(textureWidth, textureHeight); }

protected:
    class Texture* texture = nullptr;
    Vector4 color = Color::White;

    int textureWidth = 0;
    int textureHeight = 0;
};
