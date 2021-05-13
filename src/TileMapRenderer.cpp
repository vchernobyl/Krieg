#include "TileMapRenderer.h"
#include "TileMap.h"
#include "Renderer.h"
#include "Camera.h"

TileMapRenderer::TileMapRenderer(TileMap* map) : map(map) {}

void TileMapRenderer::Draw(Renderer* renderer) {
    for (auto layer : map->GetLayers()) {
	for (auto tile : layer->tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto src = tileInfo->rect;
	    auto dst = SDL_Rect { static_cast<int>(tile.x), static_cast<int>(tile.y), 32, 32 };
	    renderer->GetCamera()->ToScreenSpace(dst);
	    SDL_RenderCopyEx(renderer->GetSDLRenderer(), tileInfo->texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
	}
    }
}
