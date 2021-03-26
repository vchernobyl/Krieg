#include "TileMap.h"

#include <fstream>
#include <sstream>
#include <iostream>

TileMap TileMapLoader::Load(const char* fileName) {
    TileMap map;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName);
    if (!result) {
	SDL_Log("Failed to load map: %s", fileName);
    }

    TileSet tileSet = CreateTileSet(doc.child("map"));
    std::cout << tileSet.imageName;

    return map;
}

TileSet TileMapLoader::CreateTileSet(pugi::xml_node root) {
    pugi::xml_node node = root.child("tileset");
    TileSet tileSet;
    tileSet.imageName = node.child("image").attribute("source").value();
    tileSet.tileWidth = node.attribute("tilewidth").as_int();
    tileSet.tileHeight = node.attribute("tileheight").as_int();
    tileSet.tileCount = node.attribute("tilecount").as_int();
    tileSet.columns = node.attribute("columns").as_int();
    return tileSet;
}

const std::vector<int> TileMapLoader::LoadTileIds(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::vector<int> tileIds;
    while (std::getline(file, line)) {
	std::stringstream ss(line);
	std::string id;
	while (std::getline(ss, id, ',')) {
	    tileIds.push_back(std::stoi(id));
	}
    }
    return tileIds;
}
