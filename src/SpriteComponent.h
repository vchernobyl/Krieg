#pragma once

#include "Component.h"
#include "Math.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void Draw(class SpriteBatch& spriteBatch);
    void SetTexture(class Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    int GetTextureWidth() const { return textureWidth; }
    int GetTextureHeight() const { return textureHeight; }
    Vector2 GetSize() const { return Vector2(textureWidth, textureHeight); }

protected:
    class Texture* texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};
