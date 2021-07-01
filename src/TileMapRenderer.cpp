#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Game.h"

TileMapRenderer::TileMapRenderer(TileMap* map) : map(map) {}

void TileMapRenderer::Draw(Renderer* renderer) {
    auto tileSet = map->tileSets[0];
    int tileWidth = tileSet->tileWidth;
    int tileHeight = tileSet->tileHeight;
    //SDL_Log("w=%d, h=%d", tileSet->tileWidth, tileSet->tileHeight);
    
    for (auto layer : map->GetLayers()) {
	for (auto tile : layer->tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto rect = tileInfo->rect;

	    SDL_Rect src = {
		static_cast<int>(rect.position.x),
		static_cast<int>(rect.position.y),
		static_cast<int>(rect.size.x),
		static_cast<int>(rect.size.y)
	    };
	    
	    SDL_Rect dst =  {
		static_cast<int>(tile.x * Game::UnitsToPixels),
		static_cast<int>(tile.y * Game::UnitsToPixels),
		static_cast<int>(tileWidth * Game::UnitsToPixels),
		static_cast<int>(tileHeight * Game::UnitsToPixels)
	    };

	    renderer->GetCamera()->ToScreenSpace(dst);
	    SDL_RenderCopyEx(renderer->renderer, tileInfo->texture->texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
	}
    }
}
