#include "TileMap.h"
#include "pugixml.hpp"

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

    pugi::xml_node mapNode = doc.child("map");
    std::vector<TileSet> tileSets;
    for (pugi::xml_node node = mapNode.child("tileset"); node; node = node.next_sibling("tileset")) {
	TileSet tileSet;
	tileSet.imageName = node.child("image").attribute("source").value();
	tileSet.tileWidth = node.attribute("tilewidth").as_int();
	tileSet.tileHeight = node.attribute("tileheight").as_int();
	tileSet.tileCount = node.attribute("tilecount").as_int();
	tileSet.columns = node.attribute("columns").as_int();
	tileSets.push_back(tileSet);
    }

    return map;
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
