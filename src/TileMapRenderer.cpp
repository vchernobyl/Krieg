#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Game.h"

TileMapRenderer::TileMapRenderer(TileMap* map) : map(map) {}

void TileMapRenderer::Draw(Renderer* renderer) {
    auto tileSet = map->tileSets[0]; // We currently support only maps with a single tile set.
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();
    
    for (auto layer : map->GetLayers()) {
	for (auto tile : layer->tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto rect = tileInfo->rect;

	    // TODO: Tile source should not be using units, it's just an internal representation
	    // which won't benefit from this conversion. Needs to be kept in pixels as loaded.
	    SDL_Rect src = {
		static_cast<int>(rect.position.x * Game::UnitsToPixels),
		static_cast<int>(rect.position.y * Game::UnitsToPixels),
		static_cast<int>(rect.size.x * Game::UnitsToPixels),
		static_cast<int>(rect.size.y * Game::UnitsToPixels)
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
