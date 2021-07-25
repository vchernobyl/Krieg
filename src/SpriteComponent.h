#pragma once

#include "Component.h"
#include "Math.h"
#include "Game.h"

class Actor;
class Texture;
class Renderer;

enum SpriteEffect {
    None             = 0x0000,
    FlipHorizontally = 0x0001,
    FlipVertically   = 0x0002,
};

class SpriteComponent : public Component {
public:
    bool flipX, flipY;

    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void Draw(Renderer* renderer);
    void SetTexture(Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    Vector2 GetSize() const { return region.size * Game::PixelsToUnits; }

    void SetDrawRegion(const Rectangle& region) { this->region = region; }

protected:
    Texture* texture;
    Rectangle region;

    int drawOrder;
};
