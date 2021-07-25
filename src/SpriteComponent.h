#pragma once

#include "Component.h"
#include "Math.h"
#include "Game.h"

class Actor;
class Texture;
class Renderer;

class SpriteComponent : public Component {
public:
    bool flipX, flipY;

    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void Draw(Renderer* renderer);
    void SetTexture(Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    Vector2 GetSize() const { return Vector2(width, height) * Game::PixelsToUnits; }

    void SetDrawRegion(const Rectangle& region) { this->region = region; }

protected:
    Texture* texture;
    Rectangle region;

    int width;
    int height;
    int drawOrder;
};
