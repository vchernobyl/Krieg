#include "Actor.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

#include <SDL.h>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      flipX(false),
      flipY(false) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Renderer* renderer) {
    if (!texture) return;

    const auto width = region.size.x;
    const auto height = region.size.y;

    SDL_Rect dst;
    dst.w = static_cast<int>(width * owner->GetScale());
    dst.h = static_cast<int>(height * owner->GetScale());

    Vector2 cameraPos = renderer->GetCamera()->GetPosition();
    dst.x = static_cast<int>((owner->GetPosition().x - cameraPos.x) * Game::UnitsToPixels);
    dst.y = static_cast<int>((owner->GetPosition().y - cameraPos.y) * Game::UnitsToPixels);

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    if (flipX) spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_HORIZONTAL));
    if (flipY) spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_VERTICAL));

    SDL_Rect src;
    src.x = region.position.x;
    src.y = region.position.y;
    src.w = width;
    src.h = height;

    SDL_RenderCopyEx(renderer->renderer, texture->texture, &src, &dst, 0, nullptr, spriteFlip);
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->region = Rectangle(0.0f, 0.0f, texture->width, texture->height);
}
