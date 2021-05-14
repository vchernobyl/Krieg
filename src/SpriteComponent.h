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

    void SetDrawRegion(Rect region) { this->region = region; }

    int GetDrawOrder() const { return drawOrder; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
protected:
    class Texture* texture;
    Rect region;
    int drawOrder;
    int width;
    int height;
};
