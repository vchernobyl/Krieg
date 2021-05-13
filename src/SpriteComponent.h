#pragma once

#include "Component.h"
#include "Math.h"

#include <SDL.h>

class SpriteComponent : public Component {
public:
    bool flipX, flipY;

    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    void SetDrawRegion(Rect region) { this->region = region; }

    int GetDrawOrder() const { return drawOrder; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
protected:
    SDL_Texture* texture;
    Rect region;
    int drawOrder;
    int width;
    int height;
};
