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

struct Tile {
    Tile(int x, int y, const TileInfo* tileInfo)
	: x(x), y(y), tileInfo(tileInfo) {}

    int x;
    int y;
    const TileInfo* tileInfo;
};

struct TileMapLayer {
    TileMapLayer(const std::string& name, int width, int height, std::vector<Tile> tiles)
	: name(name), width(width), height(height), tiles(tiles) {}

    std::string name;
    int width;
    int height;
    bool isVisible = true;
    std::vector<Tile> tiles;
};

class TileMap {
public:
    ~TileMap();
    void AddLayer(TileMapLayer* layer) { layers.push_back(layer); }
    void AddTileSet(TileSet* tileSet) { tileSets.push_back(tileSet); }
    std::vector<TileMapLayer*> GetLayers() { return layers; }
private:
    std::vector<TileMapLayer*> layers;
    std::vector<TileSet*> tileSets;
};

class TileMapLoader {
public:
    TileMapLoader(class Game* game) : game(game) {}
    TileMap* Load(const std::string& fileName);
private:
    TileSet* CreateTileSet(pugi::xml_node root);
    std::vector<TileMapLayer*> CreateTileMapLayers(pugi::xml_node root, TileSet* tileSet);
    const std::vector<int> ParseTileIds(const std::string& fileName);
    std::vector<Tile> CreateTiles(const std::vector<int>& tileIds, TileSet* tileSet,
				  int layerWidth, int layerHeight);
    class Game* game;
};
