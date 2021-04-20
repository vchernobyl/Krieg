#include "Renderer.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Camera.h"
#include "SDL_image.h"
#include <algorithm>

const int WorldWidth = 32 * 42;
const int WorldHeight = 32 * 32;

Renderer::Renderer(Game* game) : game(game) {}

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

    camera = new Camera(screenWidth, screenHeight);
    camera->SetWorldSize(WorldWidth, WorldHeight);

    return true;
}

void Renderer::Shutdown() {
    delete camera;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::Begin() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Draw() {
    for (auto sprite : sprites) {
	sprite->Draw(this);
    }
}

void Renderer::DrawTexture(SDL_Texture* texture, SDL_Rect* dst, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, texture, nullptr, dst, 0, nullptr, flip);
}

void Renderer::DrawTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, texture, src, dst, 0, nullptr, flip);
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
