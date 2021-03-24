#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include "Math.h"

struct Tile {
    int id;
    SDL_Rect textureSrc;
};

struct Cell {
    int x;
    int y;
    Tile tile;
};

struct Layer {
    std::string name;
    std::vector<Tile> tiles;
    bool isVisible;
};

class TileMap {
public:
    Layer& GetLayer(const std::string& name);
    Layer& GetLayer(int index);
private:
    std::vector<Layer> layers;
};

class TileMapLoader {
public:
    TileMap Load(const std::string& fileName);
};
