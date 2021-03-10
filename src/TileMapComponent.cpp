#include "TileMapComponent.h"

const int TileWidth = 32;
const int TileHeight = 32;

TileMapComponent::TileMapComponent(Actor* owner)
    : SpriteComponent(owner) {
    tileset = owner->GetGame()->GetTexture("assets/tileset.png");
}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
    int map[] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
    int x = 0;
    int y = 0;
    int cameraX = camera->GetPosition().x;
    int cameraY = camera->GetPosition().y;
    int tiles = 0;
    for (int tile : map) {
	SDL_Rect srcrect { TileWidth * tile, TileHeight, TileWidth, TileHeight };
	SDL_Rect dstrect { x - cameraX, y - cameraY, TileWidth, TileHeight };
	if (SDL_HasIntersection(&dstrect, &camera->GetViewport())) {
	    SDL_RenderCopy(renderer, tileset, &srcrect, &dstrect);
	    tiles++;
	}
	x += TileWidth;
    }
    SDL_Log("rendered %d tiles", tiles);
}
