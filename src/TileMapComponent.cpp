#include "TileMapComponent.h"
#include <fstream>
#include <sstream>

TileMapComponent::TileMapComponent(Actor* owner, TileSet& tileSet, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      tileSet(tileSet),
      tileWidth(tileSet.GetTileWidth()),
      tileHeight(tileSet.GetTileHeight()),
      scrollSpeed(1.0f) {}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
    const Camera* camera = owner->GetGame()->GetCamera();
    const Vector2 camPos = camera->GetPosition();
    const int camX = camPos.x;
    const int camY = camPos.y;

    int y = 0;
    for (auto& tileRow : tiles) {
	int x = -1;
	for (auto tileId : tileRow) {
	    x++;
	    if (tileId < 0) continue;
	    const SDL_Rect src = tileSet.GetTile(tileId);
	    const SDL_Rect dst {
		x * tileWidth - static_cast<int>(camX * scrollSpeed),
		y * tileHeight - static_cast<int>(camY * scrollSpeed),
		tileWidth,
		tileHeight
	    };
	    if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		SDL_RenderCopy(renderer, tileSet.GetTexture(), &src, &dst);
	    }
	}
	y++;
    }
}

void TileMapComponent::LoadMap(const std::string& mapFile) {
    std::ifstream file(mapFile);
    std::string line;
    while (std::getline(file, line)) {
	std::stringstream ss(line);
	std::string str;
	std::vector<int> row;
	while (std::getline(ss, str, ',')) {
	    row.push_back(std::stoi(str));
	}
	tiles.push_back(row);
    }
}
