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
    Tile(int x, int y, const TileInfo* tileInfo)
	: x(x), y(y), tileInfo(tileInfo) {}

    int x;
    int y;
    const TileInfo* tileInfo;
};

struct TileMapLayer {
    std::string name;
    std::vector<Tile> tiles;
    int width;
    int height;
    bool isVisible = true;
};

struct TileSet {
    TileSet(SDL_Texture* image, int tileWidth, int tileHeight, int tileCount, int columns);
    const TileInfo* GetTileInfo(int id) const { return &tileInfos[id]; }
    SDL_Texture* image;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
    std::vector<TileInfo> tileInfos;
};

class TileMap {
public:
    TileMap() {}
    TileMap(TileMapLayer layer) { layers.push_back(layer); }
    const TileMapLayer& GetLayer() const { return layers.front(); }
private:
    std::vector<TileMapLayer> layers;
    std::vector<TileSet> tileSets;
};

// TODO(Refactor): This doesn't need a class, can just be a regular function instead!
class TileMapLoader {
public:
    TileMapLoader(class Game* game) : game(game) {}
    TileMap Load(const std::string& fileName);
private:
    // TODO(Refactor): Just do everything in a single Load() method, wtf!
    TileSet CreateTileSet(pugi::xml_node root);
    TileMapLayer CreateTileMapLayer(pugi::xml_node root, const TileSet& tileSet);
    const std::vector<int> ParseTileIds(const std::string& fileName);
    std::vector<Tile> CreateTiles(const std::vector<int>& tileIds, const TileSet& tileSet,
				  int layerWidth, int layerHeight);
    class Game* game;
};
