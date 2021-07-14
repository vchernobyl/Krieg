#include "TileMap.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

#include <pugixml.hpp>
#include <sstream>
#include <iostream>

TileSet::TileSet(Texture* image, int tileWidth, int tileHeight, int tileCount, int columns)
    : image(image), tileWidth(tileWidth), tileHeight(tileHeight),
      tileCount(tileCount), columns(columns) {
    const int rows = tileCount / columns;
    for (int row = 0; row < rows; ++row) {
	for (int col = 0; col < columns; ++col) {
	    Rectangle rect = Rectangle(col * tileWidth, row * tileHeight, tileWidth, tileHeight);
	    int tileId = row * columns + col;
	    TileInfo tileInfo = { tileId, image, rect };

	    tileInfos.push_back(tileInfo);
	}
    }
}

TileMap* TileMapLoader::Load(const std::string& fileName) {
    pugi::xml_document doc;
    pugi::xml_parse_result success = doc.load_file(fileName.c_str());

    auto map = new TileMap();

    if (!success) {
	SDL_Log("Failed to load map: %s", fileName.c_str());
	return map;
    }

    auto tileSet = CreateTileSet(doc.child("map"));
    map->AddTileSet(tileSet);

    auto layers = CreateTileMapLayers(doc.child("map"), tileSet);
    for (auto layer : layers) {
	map->AddLayer(layer);
    }

    auto objectGroups = CreateObjectGroups(doc.child("map"));
    for (auto group : objectGroups) {
	map->AddObjectGroup(group);
    }

    return map;
}

TileSet TileMapLoader::CreateTileSet(pugi::xml_node root) {
    auto tileSetNode = root.child("tileset");
    auto imageName = tileSetNode.child("image").attribute("source").value();
    std::stringstream imagePath;
    imagePath << "assets/" << imageName;

    return TileSet(game->GetRenderer()->GetTexture(imagePath.str()),
		   tileSetNode.attribute("tilewidth").as_int() * Game::PixelsToUnits,
		   tileSetNode.attribute("tileheight").as_int() * Game::PixelsToUnits,
		   tileSetNode.attribute("tilecount").as_int(),
		   tileSetNode.attribute("columns").as_int());
}

const std::vector<TileMapLayer> TileMapLoader::CreateTileMapLayers(pugi::xml_node root, TileSet tileSet) {
    std::vector<TileMapLayer> layers;
    for (pugi::xml_node layerNode : root.children("layer")) {
	auto name = layerNode.attribute("name").value();
	auto width = layerNode.attribute("width").as_int();
	auto height = layerNode.attribute("height").as_int();
	auto tileIds = ParseTileIds(layerNode.child_value("data"));
	auto tiles = CreateTiles(tileIds, tileSet, width, height);
	layers.push_back(TileMapLayer { name, width, height, tiles });
    }
    return layers;
}

const std::vector<Tile> TileMapLoader::CreateTiles(const std::vector<int>& tileIds, TileSet tileSet,
					     int layerWidth, int layerHeight) {
    std::vector<Tile> tiles;
    for (int row = 0; row < layerHeight; ++row) {
	for (int col = 0; col < layerWidth; ++col) {
	    int x = col * tileSet.GetTileWidth();
	    int y = row * tileSet.GetTileHeight();
	    int index = row * layerWidth + col;
	    int id = tileIds[index] - 1; // -1 because tilegid == 1
	    if (id > 0) {
		TileInfo tileInfo = tileSet.GetTileInfo(id);
		Vector2 position = Vector2(x, y);
		Tile tile = { position, tileInfo };
		tiles.push_back(tile);
	    }
	}
    }
    return tiles;
}

const std::vector<ObjectGroup> TileMapLoader::CreateObjectGroups(pugi::xml_node root) {
    std::vector<ObjectGroup> groups;
    for (pugi::xml_node objectGroupNode : root.children("objectgroup")) {
	std::vector<Rectangle> objects;
	for (pugi::xml_node objectNode : objectGroupNode.children("object")) {
	    auto x = objectNode.attribute("x").as_int();
	    auto y = objectNode.attribute("y").as_int();
	    auto width = objectNode.attribute("width").as_int();
	    auto height = objectNode.attribute("height").as_int();

	    auto position = Vector2(x, y) * Game::PixelsToUnits;
	    auto size = Vector2(width, height) * Game::PixelsToUnits;
	    auto object = Rectangle(position, size);

	    objects.push_back(object);
	}
	auto name = objectGroupNode.attribute("name").value();
	groups.push_back(ObjectGroup { name, objects });
    }
    return groups;
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
