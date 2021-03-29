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

TileMap::~TileMap() {
    for (auto layer : layers) {	delete layer; }
    for (auto tileSet : tileSets) { delete tileSet; }
    layers.clear();
    tileSets.clear();
    SDL_Log("TileMap destroyed");
}

TileMap* TileMapLoader::Load(const std::string& fileName) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());

    if (!result) {
	SDL_Log("Failed to load map: %s", fileName.c_str());
    }

    auto map = new TileMap();
    auto tileSet = CreateTileSet(doc.child("map"));
    auto layer = CreateTileMapLayer(doc.child("map"), tileSet);
    map->AddLayer(layer);
    map->AddTileSet(tileSet);

    return map;
}

TileSet* TileMapLoader::CreateTileSet(pugi::xml_node root) {
    auto tileSetNode = root.child("tileset");
    // auto imageName = tileSetNode.child("image").attribute("source").value();
    return new TileSet(game->GetTexture("assets/Tiles.png"),
		       tileSetNode.attribute("tilewidth").as_int(),
		       tileSetNode.attribute("tileheight").as_int(),
		       tileSetNode.attribute("tilecount").as_int(),
		       tileSetNode.attribute("columns").as_int());
}

TileMapLayer* TileMapLoader::CreateTileMapLayer(pugi::xml_node root, TileSet* tileSet) {
    auto layerNode = root.child("layer");
    auto name = layerNode.attribute("name").value();
    auto width = layerNode.attribute("width").as_int();
    auto height = layerNode.attribute("height").as_int();
    auto tileIds = ParseTileIds(layerNode.child_value("data"));
    auto tiles = CreateTiles(tileIds, tileSet, width, height);
    return new TileMapLayer(name, width, height, tiles);
}

std::vector<Tile> TileMapLoader::CreateTiles(const std::vector<int>& tileIds, TileSet* tileSet,
					     int layerWidth, int layerHeight) {
    std::vector<Tile> tiles;
    for (int row = 0; row < layerHeight; ++row) {
	for (int col = 0; col < layerWidth; ++col) {
	    int x = col * tileSet->tileWidth;
	    int y = row * tileSet->tileHeight;
	    int id = tileIds[row * col + col];
	    auto tileInfo = tileSet->GetTileInfo(id);
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
