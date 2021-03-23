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

struct TileSheet {
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

class TileMapParser {
public:
    TileMapParser(class Game* game);
    std::vector<class Actor*> Parse(const std::string& fileName);
private:
    std::vector<int> ParseTileIds(const std::string& fileName);
    class Game* game;
};
