#include "TileMap.h"
#include "Game.h"
#include <sstream>
#include <iostream>

TileSet::TileSet(SDL_Texture* image, int tileWidth, int tileHeight, int tileCount, int columns)
    : image(image), tileWidth(tileWidth), tileHeight(tileHeight),
      tileCount(tileCount), columns(columns) {
    const int rows = tileCount / columns;
    for (int row = 0; row < rows; ++row) {
	for (int col = 0; col < columns; ++col) {
	    SDL_Rect rect { col * tileWidth, row * tileHeight, tileWidth, tileHeight };
	    TileInfo tileInfo { row * columns + col, image, rect };
	    tileInfos.push_back(tileInfo);
	}
    }
}

TileMap TileMapLoader::Load(const std::string& fileName) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());

    if (!result) {
	SDL_Log("Failed to load map: %s", fileName.c_str());
    }

    // TODO(Bugfix): tile infos don't exist after this method scope is out!
    auto tileSet = CreateTileSet(doc.child("map"));
    auto layer = CreateTileMapLayer(doc.child("map"), tileSet);
    auto map = TileMap(layer);

    return map;
}

TileSet TileMapLoader::CreateTileSet(pugi::xml_node root) {
    auto tileSetNode = root.child("tileset");
    auto imageName = tileSetNode.child("image").attribute("source").value();
    TileSet tileSet {
	game->GetTexture(imageName),
	tileSetNode.attribute("tilewidth").as_int(),
	tileSetNode.attribute("tileheight").as_int(),
	tileSetNode.attribute("tilecount").as_int(),
	tileSetNode.attribute("columns").as_int(),
    };
    return tileSet;
}

TileMapLayer TileMapLoader::CreateTileMapLayer(pugi::xml_node root, const TileSet& tileSet) {
    TileMapLayer layer;
    auto layerNode = root.child("layer");
    layer.name = layerNode.attribute("name").value();
    layer.width = layerNode.attribute("width").as_int();
    layer.height = layerNode.attribute("height").as_int();
    auto tileIds = ParseTileIds(layerNode.child_value("data"));
    layer.tiles = CreateTiles(tileIds, tileSet, layer.width, layer.height);
    return layer;
}

std::vector<Tile> TileMapLoader::CreateTiles(const std::vector<int>& tileIds, const TileSet& tileSet,
					     int layerWidth, int layerHeight) {
    std::vector<Tile> tiles;
    for (int row = 0; row < layerHeight; ++row) {
	for (int col = 0; col < layerWidth; ++col) {
	    int x = col * tileSet.tileWidth;
	    int y = row * tileSet.tileHeight;
	    auto tileInfo = tileSet.GetTileInfo(row * col + col);
	    auto tile = Tile(x, y, tileInfo);
	    tiles.push_back(tile);
	}
    }
    return tiles;
}

const std::vector<int> TileMapLoader::ParseTileIds(const std::string& data) {
    std::istringstream inputStream(data);
    std::string line;
    std::vector<int> tileIds;

    while (std::getline(inputStream, line)) {
	std::stringstream ss(line);
	std::string id;
	while (std::getline(ss, id, ',')) {
	    tileIds.push_back(std::stoi(id));
	}
    }

    return tileIds;
}
