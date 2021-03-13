#include "TileMapComponent.h"

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
	    int tileId = tiles[x + y * mapRows];
	    const SDL_Rect src = tileSet.GetTile(tileId);
	    const SDL_Rect dst { x * tileWidth - camX, y * tileHeight - camY, tileWidth, tileHeight };
	    if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		SDL_RenderCopy(renderer, texture, &src, &dst);
	    }
	}
    }
}

void TileMapComponent::LoadMap(const std::string& mapFile) {
    tiles = {
	5, 3, 2, 3, 2, 3, 2, 3, 2, 3,
	48, 48, 1, 48, 1, 48, 1, 48, 1, 48,
	100, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	2, 5, 2, 5, 2, 5, 2, 5, 2, 5,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 3, 0, 3, 0, 3, 0, 3, 0, 3,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    };
    mapCols = 10;
    mapRows = 8;
}
