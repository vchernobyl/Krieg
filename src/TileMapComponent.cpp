#include "TileMapComponent.h"

const int TileWidth = 32;
const int TileHeight = 32;

struct TileSet {
    int rows;
    int cols;
};

TileMapComponent::TileMapComponent(Actor* owner)
    : SpriteComponent(owner) {
    tileset = owner->GetGame()->GetTexture("assets/Tiles.png");
}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
    int map[] = {
	2, 3, 2, 3, 2, 3, 2, 3, 2, 3,
	1, 48, 1, 48, 1, 48, 1, 48, 1, 48,
	0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	2, 5, 2, 5, 2, 5, 2, 5, 2, 5,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
	0, 3, 0, 3, 0, 3, 0, 3, 0, 3,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    };

    TileSet tileSet { 24, 8 };

    const int height = 8;
    const int width = 10;
    const Camera* camera = owner->GetGame()->GetCamera();
    const Vector2 camPos = camera->GetPosition();
    const int camX = camPos.x;
    const int camY = camPos.y;

    int renderedObjects = 0;
    for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
	    int tileId = map[x + y * width];
	    int row = tileId / tileSet.rows;
	    int col = tileId % tileSet.rows;
	    const SDL_Rect src { TileWidth * col, TileHeight * row, TileWidth, TileHeight };
	    const SDL_Rect dst { x * TileWidth - camX, y * TileHeight - camY, TileWidth, TileHeight };
	    if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		++renderedObjects;
		SDL_RenderCopy(renderer, tileset, &src, &dst);
	    }
	}
    }

    SDL_Log("Rendered %d objects", renderedObjects);
}
