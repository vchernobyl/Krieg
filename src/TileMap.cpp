#include "TileMap.h"
#include "Game.h"
#include <sstream>
#include <iostream>

TileSet::TileSet(SDL_Texture* image, int tileWidth, int tileHeight, int tileCount, int columns)
    : image(image), tileWidth(tileWidth), tileHeight(tileHeight),
      tileCount(tileCount), columns(columns) {
    const int rows = tileCount / columns;
    int id = 0; // == row * rows + col
    for (int row = 0; row < rows; ++row) {
	for (int col = 0; col < columns; ++col) {
	    SDL_Rect rect { col * tileWidth, row * tileHeight, tileWidth, tileHeight };
	    TileInfo tileInfo { id++, image, rect };
	    tileInfos.push_back(tileInfo);
	}
    }
}

TileMap TileMapLoader::Load(const std::string& fileName) {
    TileMap map;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());

    if (!result) {
	SDL_Log("Failed to load map: %s", fileName.c_str());
    }

    auto tileSet = CreateTileSet(doc.child("map"));
    auto layer = CreateTileMapLayer(doc.child("map"), tileSet);

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
    layer.tiles = {}; // TODO: Parse csv data and create tiles
    auto tileIds = ParseTileIds(layerNode.child_value("data"));
    return layer;
}

std::vector<Tile> TileMapLoader::CreateTiles(const std::vector<int>& tileIds, const TileSet& tileSet) {
    std::vector<Tile> result;
    // for (int row = 0; y < layerHeight; ++y) {
    // 	for (int col = 0; y < layerWidth; ++x) {
    // 	    int x = col * tileSet.tileWidth;
    // 	    int y = row * tileSet.tileHeight;
    return result;
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
