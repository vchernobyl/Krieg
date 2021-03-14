#pragma once

#include "SpriteComponent.h"
#include "TileSet.h"
#include <string>
#include <vector>

using MapLayer = std::vector<std::vector<int> >;

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(Actor* owner);
    void Draw(SDL_Renderer* renderer) override;
    void LoadMap(const std::vector<std::string>& files);
private:
    TileSet tileSet;
    int tileWidth;
    int tileHeight;
    std::vector<MapLayer> layers;
};
