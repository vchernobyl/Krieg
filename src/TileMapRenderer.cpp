#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Texture.h"
#include "Game.h"

TileMapRenderer::TileMapRenderer(TileMap tileMap) : tileMap(tileMap) {
    const auto tileSet = tileMap.GetTileSets().front();
    tileWidth = tileSet.GetTileWidth() * Game::PixelsToUnits;
    tileHeight = tileSet.GetTileHeight() * Game::PixelsToUnits;
}

void TileMapRenderer::Draw(Renderer* renderer) {
    for (auto layer : tileMap.GetLayers()) {
	for (auto tile : layer.tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto src = Rectangle(tileInfo.source.position, tileInfo.source.size);
	    auto dst = Rectangle(tile.position * Game::PixelsToUnits, Vector2(tileWidth, tileHeight));
	    renderer->DrawTexture(tileInfo.texture, src, dst, 0, SpriteEffect::None);
	}
    }
}
