#pragma once

#include "Math.h"

#include <string>
#include <vector>

class Texture;
class Game;

struct TileInfo {
    int id;
    Texture* texture;
    Rectangle rect;
};

struct Tile {
    Vector2 position;
    TileInfo tileInfo;
};

struct TileMapLayer {
    std::string name;
    int width;
    int height;
    std::vector<Tile> tiles;
};

struct ObjectGroup {
    std::string name;
    std::vector<Rectangle> objects;
};

class TileSet {
public:
    TileSet(Texture* image, int tileWidth, int tileHeight, int tileCount, int columns);

    const TileInfo& GetTileInfo(int id) const { return tileInfos[id]; }
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

class TileMap {
public:
    void AddLayer(TileMapLayer layer) { layers.push_back(layer); }
    void AddTileSet(TileSet tileSet) { tileSets.push_back(tileSet); }
    void AddObjectGroup(ObjectGroup objectGroup) { objectGroups.push_back(objectGroup); }

    const std::vector<TileMapLayer>& GetLayers() { return layers; }
    const std::vector<ObjectGroup>& GetObjectGroups() { return objectGroups; }

private:
    friend class TileMapRenderer;
    
    std::vector<TileMapLayer> layers;
    std::vector<TileSet> tileSets;
    std::vector<ObjectGroup> objectGroups;
};

// Forward declaration for the pugi::xml_node.
namespace pugi {
    class xml_node;
};

class TileMapLoader {
public:
    TileMapLoader(Game* game) : game(game) {}
    TileMap Load(const std::string& fileName);
private:
    TileSet CreateTileSet(pugi::xml_node root);
    const std::vector<TileMapLayer> CreateTileMapLayers(pugi::xml_node root, TileSet tileSet);
    const std::vector<Tile> CreateTiles(const std::vector<int>& tileIds, TileSet tileSet, int layerWidth, int layerHeight);
    const std::vector<ObjectGroup> CreateObjectGroups(pugi::xml_node root);
    const std::vector<int> ParseTileIds(const std::string& fileName);
    Game* game;
};
