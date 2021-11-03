#pragma once

#include "Component.h"
#include "Math.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void Draw(class SpriteBatch& spriteBatch);
    void SetTexture(class Texture* texture);
    void SetColor(const Vector4& color) { this->color = color; }

    int GetDrawOrder() const { return drawOrder; }
    int GetTextureWidth() const { return textureWidth; }
    int GetTextureHeight() const { return textureHeight; }
    Vector2 GetSize() const { return Vector2(textureWidth, textureHeight); }

protected:
    class Texture* texture = nullptr;
    Vector4 color = Color::White;

    int drawOrder = 0;
    int textureWidth = 0;
    int textureHeight = 0;
};
