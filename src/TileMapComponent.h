#pragma once

#include "SpriteComponent.h"
#include "TileSet.h"
#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(Actor* owner, int drawOrder = 100);
    void Draw(SDL_Renderer* renderer) override;
    void LoadMap(const std::string& mapFile);
private:
    TileSet tileSet;
    int tileWidth;
    int tileHeight;
    std::vector<std::vector<int> > tiles;
};
