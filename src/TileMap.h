#pragma once

#include "Math.h"

#include <string>
#include <vector>

class Texture;

struct TileInfo {
    int id;
    Texture* texture;
    Rectangle rect;
};

struct Tile {
    Vector2 position;
    const TileInfo* tileInfo;
};

class TileSet {
public:
    TileSet(Texture* image, int tileWidth, int tileHeight, int tileCount, int columns);

    const TileInfo* GetTileInfo(int id) const { return &tileInfos[id]; }
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }

private:
    Texture* image;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
    std::vector<TileInfo> tileInfos;
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
    ObjectGroup(const std::string& name, std::vector<Rectangle> objects)
	: name(name), objects(objects) {}

    std::string name;
    std::vector<Rectangle> objects;
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
    friend class TileMapRenderer;
    
    std::vector<TileMapLayer*> layers;
    std::vector<TileSet*> tileSets;
    std::vector<ObjectGroup*> objectGroups;
};

// Forward declaration for the pugi::xml_node.
namespace pugi {
    class xml_node;
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
