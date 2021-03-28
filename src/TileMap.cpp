#include "TileMap.h"

#include <sstream>
#include <iostream>

TileMap TileMapLoader::Load(const std::string& fileName) {
    TileMap map;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());
    if (!result) {
	SDL_Log("Failed to load map: %s", fileName.c_str());
    }

    auto tileSet = CreateTileSet(doc.child("map"));
    std::cout << tileSet.imageName << std::endl;

    auto layer = CreateTileMapLayer(doc.child("map"));
    std::cout << "Layer info: ";
    std::cout << layer.name << std::endl;
    std::cout << layer.width << std::endl;
    std::cout << layer.height << std::endl;
    return map;
}

TileSet TileMapLoader::CreateTileSet(pugi::xml_node root) {
    auto tileSetNode = root.child("tileset");
    TileSet tileSet;
    tileSet.imageName = tileSetNode.child("image").attribute("source").value();
    tileSet.tileWidth = tileSetNode.attribute("tilewidth").as_int();
    tileSet.tileHeight = tileSetNode.attribute("tileheight").as_int();
    tileSet.tileCount = tileSetNode.attribute("tilecount").as_int();
    tileSet.columns = tileSetNode.attribute("columns").as_int();
    return tileSet;
}

TileMapLayer TileMapLoader::CreateTileMapLayer(pugi::xml_node root) {
    TileMapLayer layer;
    auto layerNode = root.child("layer");
    layer.name = layerNode.attribute("name").value();
    layer.width = layerNode.attribute("width").as_int();
    layer.height = layerNode.attribute("height").as_int();
    layer.tiles = {}; // TODO: Parse csv data and create tiles
    auto tileIds = ParseTileIds(layerNode.child_value("data"));
    return layer;
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
