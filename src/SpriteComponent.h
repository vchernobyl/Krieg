#pragma once

#include "Component.h"
#include "Math.h"
#include "Game.h"

// TODO: This should probably be moved to the Texture class.
enum SpriteEffect {
    None             = 0,
    FlipHorizontally = 1,
    FlipVertically   = 2,
};

class SpriteComponent : public Component {
public:
    bool flipX, flipY;

    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void Draw(class Shader* shader);
    void SetTexture(class Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    Vector2 GetSize() const { return region.size * Game::PixelsToUnits; }

    void SetDrawRegion(const Rectangle& region) { this->region = region; }

protected:
    class Texture* texture;
    Rectangle region;

    int drawOrder;
};
