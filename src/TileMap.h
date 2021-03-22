#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "Math.h"

struct TileInfo {
    int tileId;
    std::string& texture;
    SDL_Rect tileSrc;
};

struct Tile {
    TileInfo* props;
    int x;
    int y;
};

struct TileSet {
    SDL_Texture* texture;
    Vector2 imageSize;
    int columns;
    int rows;
    Vector2 tileSize;
};

struct Layer {
    std::vector<Tile*> tiles;
    bool isVisible;
};
