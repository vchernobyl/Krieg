#pragma once

#include "SpriteComponent.h"
#include "TileSet.h"

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(Actor* owner);
    void Draw(SDL_Renderer* renderer) override;
private:
    TileSet tileSet;
    int tileWidth;
    int tileHeight;
};
