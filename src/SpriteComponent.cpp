#include "Actor.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"
#include "Texture.h"

#include <SDL.h>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      flipX(false),
      flipY(false),
      width(0),
      height(0) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Renderer* renderer) {
    if (!texture) return;

    SDL_Rect dst;
    dst.w = static_cast<int>(width * owner->GetScale() * Game::UnitsToPixels);
    dst.h = static_cast<int>(height * owner->GetScale() * Game::UnitsToPixels);

    Vector2 cameraPos = renderer->GetCamera()->GetPosition();
    dst.x = static_cast<int>((owner->GetPosition().x - cameraPos.x) * Game::UnitsToPixels);
    dst.y = static_cast<int>((owner->GetPosition().y - cameraPos.y) * Game::UnitsToPixels);

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    if (flipX) spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_HORIZONTAL));
    if (flipY) spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_VERTICAL));

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = static_cast<int>(width * Game::UnitsToPixels);
    src.h = static_cast<int>(height * Game::UnitsToPixels);

    SDL_RenderCopyEx(renderer->renderer, texture->texture, &src, &dst, 0, nullptr, spriteFlip);
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->width = texture->width * Game::PixelsToUnits;
    this->height = texture->height * Game::PixelsToUnits;
}
