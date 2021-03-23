#include "TileMap.h"
#include "Actor.h"
#include "Game.h"

#include <fstream>
#include <sstream>

TileMapParser::TileMapParser(Game* game) : game(game) {}

std::vector<Actor*> Parse(const std::string& fileName) {
    std::vector<Actor*> v;
    return v;
}

std::vector<int> ParseTileIds(const std::string& fileName) {
    std::ifstream fileStream(fileName);
    std::string line;
    std::vector<int> tileIds;
    while (std::getline(fileStream, line)) {
	std::stringstream ss(line);
	std::string str;
	while (std::getline(ss, str, ',')) {
	    tileIds.push_back(std::stoi(str));
	}
    }
    fileStream.close();
    return tileIds;
}
