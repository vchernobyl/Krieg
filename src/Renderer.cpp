#include "Renderer.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Texture.h"
#include "ParticleEmitterComponent.h"
#include "DebugRenderer.h"

#include <SDL_image.h>
#include <algorithm>

Renderer::Renderer(Game* game) : game(game) {}

bool Renderer::Initialize(int windowWidth, int windowHeight) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	return false;
    }

    window = SDL_CreateWindow("Game", 100, 100, windowWidth, windowHeight, 0);
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

    windowSize = Vector2(windowWidth, windowHeight);

    return true;
}

void Renderer::Shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::UnloadData() {
    for (auto iter : textures) {
	iter.second->Unload();
	delete iter.second;
    }
    textures.clear();
}

void Renderer::Begin() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Draw() {
    for (auto sprite : sprites) {
	sprite->Draw(this);
    }

    for (auto emitter : particles) {
	emitter->Draw(this);
    }

    DebugRenderer::Draw(this);
}

void Renderer::End() {
    SDL_RenderPresent(renderer);
}

void Renderer::DrawTexture(const Texture* texture, const Rectangle& src, const Rectangle& dst,
			   double angle, SpriteEffect effect) {
    SDL_Rect srcRect;
    srcRect.x = src.position.x;
    srcRect.y = src.position.y;
    srcRect.w = src.size.x;
    srcRect.h = src.size.y;

    SDL_Rect dstRect;
    dstRect.x = (dst.position.x - cameraView.x) * Game::UnitsToPixels;
    dstRect.y = (dst.position.y - cameraView.y) * Game::UnitsToPixels;
    dstRect.w = dst.size.x * Game::UnitsToPixels;
    dstRect.h = dst.size.y * Game::UnitsToPixels;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if ((effect & SpriteEffect::FlipHorizontally) != 0)
	flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);

    if ((effect & SpriteEffect::FlipVertically) != 0)
	flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

    SDL_RenderCopyEx(renderer, texture->texture, &srcRect, &dstRect, angle, nullptr, flip);
}

Texture* Renderer::GetTexture(const std::string& fileName) {
    Texture* tex = nullptr;
    auto iter = textures.find(fileName);
    if (iter != textures.end()) {
	tex = iter->second;
    } else {
	tex = new Texture();
	if (tex->Load(fileName, renderer)) {
	    textures.emplace(fileName, tex);
	} else {
	    delete tex;
	    tex = nullptr;
	}
    }
    return tex;
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

void Renderer::AddParticles(ParticleEmitterComponent* emitter) {
    int drawOrder = emitter->GetDrawOrder();
    auto iter = particles.begin();
    while (iter != particles.end() && drawOrder > (*iter)->GetDrawOrder()) {
	++iter;
    }
    particles.insert(iter, emitter);
}

void Renderer::RemoveParticles(ParticleEmitterComponent* emitter) {
    auto iter = std::find(particles.begin(), particles.end(), emitter);
    if (iter != particles.end()) {
	particles.erase(iter);
    }
}
