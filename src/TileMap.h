#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "Math.h"

struct TileInfo {
    int id;
    SDL_Texture* texture;
    SDL_Rect textureSrc;
};

// Tiles are shared by the cells. There should be no more tiles than there are
// in the tile set.
struct Tile {
    int x;
    int y;
    TileInfo* tile;
};

struct TileMapLayer {
    TileMapLayer(int width, int height) : width(width), height(height) {}

    std::vector<Tile> tiles;
    int width;
    int height;
    bool isVisible;
};

class TileMap {
public:
    TileMapLayer& GetLayer(const std::string& name);
    TileMapLayer& GetLayer(int index);
    const std::vector<TileMapLayer>& GetLayers() const { return layers; }
private:
    const std::vector<TileMapLayer> layers;
};

struct TileSet {
    SDL_Texture* tileSheet;
    Vector2 tileSheetSize;
    Vector2 tileSize;
    int columns;
    int rows;
};

struct TileMapConfig {
    int width;
    int height;
    std::string fileName;
    TileSet tileSet;
};

class TileMapLoader {
public:
    TileMap Load(const TileMapConfig& config);
private:
    const std::vector<int> LoadTileIds(const std::string& fileName);
};
