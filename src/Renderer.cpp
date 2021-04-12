#include "Renderer.h"
#include "DebugRenderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "TileMap.h"
#include "Game.h"
#include "Camera.h"
#include "Actor.h"
#include "Math.h"
#include "SDL.h"
#include "SDL_image.h"
#include <algorithm>

Renderer::Renderer(Game* game) : game(game), camera(game->GetCamera()) {}

bool Renderer::Initialize(int screenWidth, int screenHeight) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	return false;
    }

    window = SDL_CreateWindow("Game", 100, 100, screenWidth, screenHeight, 0);
    if (!window) {
	SDL_Log("Unable to create a window: %s", SDL_GetError());
	return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
	SDL_Log("Unable to create a renderer: %s", SDL_GetError());
	return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
	return false;
    }

    // TODO: This is just for testing purposes. Move this out of here later.
    TileMapLoader mapLoader(game);
    map = mapLoader.Load("assets/test.tmx");

    return true;
}

void Renderer::Shutdown() {
    delete map;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::Begin() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Draw() {
    for (auto layer : map->GetLayers()) {
	for (auto tile : layer->tiles) {
	    auto tileInfo = tile.tileInfo;
	    SDL_Rect dst = SDL_Rect {
		static_cast<int>(tile.x - camera->GetPosition().x),
		static_cast<int>(tile.y - camera->GetPosition().y),
		32,
		32
	    };
	    SDL_RenderCopy(renderer, tileInfo->texture, &(tileInfo->rect), &dst);
	}
    }

    for (auto sprite : sprites) {
	sprite->Draw(renderer);
    }
}

void Renderer::End() {
    SDL_RenderPresent(renderer);
}

void Renderer::AddSprite(SpriteComponent* sprite) {
    int drawOrder = sprite->GetDrawOrder();
    auto iter = sprites.begin();
    while (iter != sprites.end() && drawOrder > (*iter)->GetDrawOrder()) {
	++iter;
    }
    sprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(sprites.begin(), sprites.end(), sprite);
    if (iter != sprites.end()) {
	sprites.erase(iter);
    }
}
