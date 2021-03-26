#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "Math.h"
#include "pugixml.hpp"

struct TileInfo {
    int id;
    SDL_Texture* texture;
    SDL_Rect textureSrc;
};

struct Tile {
    int x;
    int y;
    TileInfo* tile;
};

struct TileMapLayer {
    std::vector<Tile> tiles;
    int width;
    int height;
    bool isVisible;
};

struct TileSet {
    const char* imageName;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
};

class TileMap {
public:
    TileMapLayer& GetLayer(const std::string& name);
    TileMapLayer& GetLayer(int index);
    const std::vector<TileMapLayer>& GetLayers() const { return layers; }
private:
    const std::vector<TileMapLayer> layers;
};

class TileMapLoader {
public:
    TileMap Load(const char* fileName);
private:
    TileSet CreateTileSet(pugi::xml_node root);
    const std::vector<int> LoadTileIds(const std::string& fileName);
};
