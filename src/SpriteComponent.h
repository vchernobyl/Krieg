#pragma once

#include "Component.h"
#include "Maths.h"

class SpriteComponent : public DrawableComponent {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);

    void Draw(class SpriteBatch& spriteBatch) override;
    void SetTexture(class Texture* texture);
    void SetColor(const Vector4& color) { this->color = color; }
    void SetRect(int x, int y, int width, int height);
    const Vector4& GetColor() const { return color; }

    Vector2 GetSize() const;

protected:
    class Texture* texture = nullptr;
    Vector4 color = Color::White;
    Vector4 rect;
};
