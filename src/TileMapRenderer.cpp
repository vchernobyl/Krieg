#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Game.h"

TileMapRenderer::TileMapRenderer(TileMap tileMap) : tileMap(tileMap) {}

void TileMapRenderer::Draw(Renderer* renderer) {
    TileSet tileSet = tileMap.GetTileSets().front(); // We currently support only maps with a single tile set.
    int tileWidth = tileSet.GetTileWidth();
    int tileHeight = tileSet.GetTileHeight();
    
    for (auto layer : tileMap.GetLayers()) {
	for (auto tile : layer.tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto rect = tileInfo.rect;

	    // TODO: Tile source should not be using units, it's just an internal representation
	    // which won't benefit from this conversion. Needs to be kept in pixels as loaded.
	    SDL_Rect src;
	    src.x = static_cast<int>(rect.position.x * Game::UnitsToPixels);
	    src.y = static_cast<int>(rect.position.y * Game::UnitsToPixels);
	    src.w = static_cast<int>(rect.size.x * Game::UnitsToPixels);
	    src.h = static_cast<int>(rect.size.y * Game::UnitsToPixels);
	    
	    SDL_Rect dst;
	    dst.w = static_cast<int>(tileWidth * Game::UnitsToPixels);
	    dst.h = static_cast<int>(tileHeight * Game::UnitsToPixels);

	    Vector2 cameraPos = renderer->GetCamera()->GetPosition();
	    dst.x = static_cast<int>((tile.position.x - cameraPos.x) * Game::UnitsToPixels);
	    dst.y = static_cast<int>((tile.position.y - cameraPos.y) * Game::UnitsToPixels);

	    SDL_RenderCopyEx(renderer->renderer, tileInfo.texture->texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
	}
    }
}
