#pragma once

#include "TileMap.h"

// TODO: Move this guy to the TileMap header.
class TileMapRenderer {
public:
    TileMapRenderer(TileMap tileMap);
    void Draw(class Renderer* renderer);
private:
    TileMap tileMap;

    float tileWidth;
    float tileHeight;
};
