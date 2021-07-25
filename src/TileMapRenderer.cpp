#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Game.h"

TileMapRenderer::TileMapRenderer(TileMap tileMap) : tileMap(tileMap) {}

void TileMapRenderer::Draw(Renderer* renderer) {
    auto tileSet = tileMap.GetTileSets().front();
    auto tileWidth = tileSet.GetTileWidth();
    auto tileHeight = tileSet.GetTileHeight();
    
    for (auto layer : tileMap.GetLayers()) {
	for (auto tile : layer.tiles) {
	    auto tileInfo = tile.tileInfo;

	    // TODO (Refactoring): source should be already in pixels, not units!
	    auto srcRect = tileInfo.rect;
	    auto src = Rectangle(srcRect.position * Game::UnitsToPixels, srcRect.size * Game::UnitsToPixels);
	    auto dst = Rectangle(tile.position, Vector2(tileWidth, tileHeight));
	    renderer->DrawTexture(tileInfo.texture, src, dst, 0, SpriteEffect::None);
	}
    }
}
