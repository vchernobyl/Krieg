#pragma once

#include "Component.h"
#include "Math.h"

class SpriteComponent : public Component {
public:
    bool flipX, flipY;

    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Renderer* renderer);
    virtual void SetTexture(class Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    Vector2 GetSize() const { return Vector2(width, height); }

protected:
    class Texture* texture;
    int drawOrder;
    float width;
    float height;
};
