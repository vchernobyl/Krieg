#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "Math.h"
#include "pugixml.hpp"

struct TileInfo {
    TileInfo(int id, SDL_Texture* texture, SDL_Rect rect)
	: id(id), texture(texture), rect(rect) {}

    int id;
    SDL_Texture* texture;
    SDL_Rect rect;
};

struct Tile {
    int x;
    int y;
    TileInfo* tile;
};

struct TileMapLayer {
    std::string name;
    std::vector<Tile> tiles;
    int width;
    int height;
    bool isVisible = true;
};

class TileSet {
public:
    TileSet(SDL_Texture* image, int tileWidth, int tileHeight, int tileCount, int columns);
    const TileInfo* GetTileInfo(int id) const { return &tileInfos[id]; }
private:
    SDL_Texture* image;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
    std::vector<TileInfo> tileInfos;
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
    TileMapLoader(class Game* game) : game(game) {}
    TileMap Load(const std::string& fileName);
private:
    TileSet CreateTileSet(pugi::xml_node root);
    TileMapLayer CreateTileMapLayer(pugi::xml_node root, const TileSet& tileSet);
    const std::vector<int> ParseTileIds(const std::string& fileName);
    std::vector<Tile> CreateTiles(const std::vector<int>& tileIds, const TileSet& tileSet);
    class Game* game;
};
