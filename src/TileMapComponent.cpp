#include "TileMapComponent.h"
#include <fstream>
#include <sstream>

TileMapComponent::TileMapComponent(Actor* owner)
    : SpriteComponent(owner) {
    texture = owner->GetGame()->GetTexture("assets/Tiles.png");
    tileSet = TileSet(texture, 32, 32);
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();
}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
    const Camera* camera = owner->GetGame()->GetCamera();
    const Vector2 camPos = camera->GetPosition();
    const int camX = camPos.x;
    const int camY = camPos.y;

    for (auto& layer : layers) {
	int y = 0;
	for (auto& tileRow : layer) {
	    int x = -1;
	    for (auto tileId : tileRow) {
		x++;
		if (tileId < 0) continue;
		const SDL_Rect src = tileSet.GetTile(tileId);
		const SDL_Rect dst { x * tileWidth - camX, y * tileHeight - camY, tileWidth, tileHeight };
		if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		    SDL_RenderCopy(renderer, texture, &src, &dst);
		}
	    }
	    y++;
	}
    }
}

void TileMapComponent::LoadMap(const std::vector<std::string>& files) {
    for (auto& mapFile : files) {
	std::ifstream file(mapFile);
	std::string line;
	MapLayer layer;
	while (std::getline(file, line)) {
	    std::stringstream ss(line);
	    std::string str;
	    std::vector<int> row;
	    while (std::getline(ss, str, ',')) {
		row.push_back(std::stoi(str));
	    }
	    layer.push_back(row);
	}
	layers.push_back(layer);
    }
}
