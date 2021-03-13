#include "TileMapComponent.h"

TileMapComponent::TileMapComponent(Actor* owner)
    : SpriteComponent(owner) {
    SDL_Texture* texture = owner->GetGame()->GetTexture("assets/Tiles.png");
    tileSet = TileSet(texture, 24, 8);
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
	    const SDL_Rect src = tileSet.GetTile(tileId);
	    const SDL_Rect dst {
		x * tileSet.GetTileWidth() - camX,
		y * tileSet.GetTileHeight() - camY,
		tileSet.GetTileWidth(),
		tileSet.GetTileHeight()
	    };
	    if (SDL_HasIntersection(&dst, &camera->GetViewport())) {
		++renderedObjects;
		SDL_RenderCopy(renderer, tileSet.GetTexture(), &src, &dst);
	    }
	}
    }
}
