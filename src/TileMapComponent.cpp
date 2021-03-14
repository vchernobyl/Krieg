#include "TileMapComponent.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMapComponent::TileMapComponent(Actor* owner)
    : SpriteComponent(owner),
      mapCols(0),
      mapRows(0) {
    texture = owner->GetGame()->GetTexture("assets/Tiles.png");
    tileSet = TileSet(texture, 24, 8);
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();
}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
    const Camera* camera = owner->GetGame()->GetCamera();
    const Vector2 camPos = camera->GetPosition();
    const int camX = camPos.x;
    const int camY = camPos.y;

    for (int y = 0; y < mapRows; y++) {
	for (int x = 0; x < mapCols; x++) {
	    int tileId = tiles[x + y * mapCols];
	    if (tileId < 0) continue;
	    const SDL_Rect src = tileSet.GetTile(tileId);
	    const SDL_Rect dst { x * tileWidth - camX, y * tileHeight - camY, tileWidth, tileHeight };
	    if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		SDL_RenderCopy(renderer, texture, &src, &dst);
	    }
	}
    }
}

void TileMapComponent::LoadMap(const std::string& mapFile) {
    // TODO: Refactor!!!
    int height = 0;
    int width = 0;
    std::ifstream file(mapFile);
    std::string line;
    while (std::getline(file, line)) {
	height++;
	std::stringstream ss(line);
	std::string str;
	while (std::getline(ss, str, ',')) {
	    tiles.push_back(std::stoi(str));
	    width++;
	}
    }

    mapCols = width / height;
    mapRows = height;
}
