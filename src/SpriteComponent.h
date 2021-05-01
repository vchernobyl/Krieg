#pragma once

#include "Component.h"
#include "SDL.h"
#include "Math.h"

enum SpriteFlip {
    None = SDL_FLIP_NONE,
    Horizontal = SDL_FLIP_HORIZONTAL,
    Vertical = SDL_FLIP_VERTICAL
};

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetFlip(SDL_RendererFlip flip) { this->flip = flip; }
    void SetRegion(SDL_Rect region) { this->region = region; }

    int GetDrawOrder() const { return drawOrder; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
protected:
    SDL_Texture* texture;
    SDL_Rect region;
    SDL_RendererFlip flip;
    int drawOrder;
    int width;
    int height;
};
