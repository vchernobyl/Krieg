#include "TileMap.h"

#include <fstream>
#include <sstream>

TileMap TileMapLoader::Load(const TileMapConfig& config) {
    TileMap map;
    const std::vector<int> tileIds = LoadTileIds("");
    return map;
}

const std::vector<int> LoadTileIds(const std::string& fileName) {
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
