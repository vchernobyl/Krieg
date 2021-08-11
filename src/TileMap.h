#pragma once

#include "Math.h"

#include <string>
#include <vector>

class Texture;
class Game;

struct TileInfo {
    int id;
    Texture* texture;
    Rectangle source;
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
    // TODO: Pass the texture directly instead of game.
    TileMap(Game* game, const std::string& filename);

    const std::vector<TileMapLayer>& GetLayers() const { return layers; }
    const std::vector<TileSet>& GetTileSets() const { return tileSets; }
    const std::vector<ObjectGroup>& GetObjectGroups() const { return objectGroups; }

private:
    std::vector<TileMapLayer> layers;
    std::vector<TileSet> tileSets;
    std::vector<ObjectGroup> objectGroups;
};
