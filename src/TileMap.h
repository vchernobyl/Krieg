#pragma once

#include "Math.h"
#include "pugixml.hpp"

#include <string>
#include <vector>

class Texture;

struct TileInfo {
    TileInfo(int id, Texture* texture, Rect rect)
	: id(id), texture(texture), rect(rect) {}

    int id;
    Texture* texture;
    Rect rect;
};

struct TileSet {
    TileSet(Texture* image, int tileWidth, int tileHeight, int tileCount, int columns);
    const TileInfo* GetTileInfo(int id) const { return &tileInfos[id]; }
    Texture* image;
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

struct ObjectGroup {
    ObjectGroup(const std::string& name, std::vector<Rect> objects)
	: name(name), objects(objects) {}

    std::string name;
    std::vector<Rect> objects;
};

class TileMap {
public:
    ~TileMap();
    void AddLayer(TileMapLayer* layer) { layers.push_back(layer); }
    void AddTileSet(TileSet* tileSet) { tileSets.push_back(tileSet); }
    void AddObjectGroup(ObjectGroup* objectGroup) { objectGroups.push_back(objectGroup); }
    const std::vector<TileMapLayer*>& GetLayers() { return layers; }
    const std::vector<ObjectGroup*>& GetObjectGroups() { return objectGroups; }
private:
    std::vector<TileMapLayer*> layers;
    std::vector<TileSet*> tileSets;
    std::vector<ObjectGroup*> objectGroups;
};

class TileMapLoader {
public:
    TileMapLoader(class Game* game) : game(game) {}
    TileMap* Load(const std::string& fileName);
private:
    TileSet* CreateTileSet(pugi::xml_node root);
    const std::vector<TileMapLayer*> CreateTileMapLayers(pugi::xml_node root, TileSet* tileSet);
    const std::vector<Tile> CreateTiles(const std::vector<int>& tileIds, TileSet* tileSet,
				  int layerWidth, int layerHeight);
    const std::vector<ObjectGroup*> CreateObjectGroups(pugi::xml_node root);
    const std::vector<int> ParseTileIds(const std::string& fileName);
    class Game* game;
};
