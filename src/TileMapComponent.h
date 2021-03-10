#pragma once

#include "SpriteComponent.h"

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(Actor* owner);
    void Draw(SDL_Renderer* renderer) override;
private:
    SDL_Texture* tileset;
};
