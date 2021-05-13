#include "Actor.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"

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
    dst.w = static_cast<int>(region.size.x * owner->GetScale());
    dst.h = static_cast<int>(region.size.y * owner->GetScale());
    dst.x = static_cast<int>(owner->GetPosition().x);
    dst.y = static_cast<int>(owner->GetPosition().y);
    renderer->GetCamera()->ToScreenSpace(dst);

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    if (flipX) {
	spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_HORIZONTAL));
    }
    if (flipY) {
	spriteFlip = (SDL_RendererFlip (spriteFlip | SDL_FLIP_VERTICAL));
    }

    SDL_Rect src = {
	static_cast<int>(region.position.x),
	static_cast<int>(region.position.y),
	static_cast<int>(region.size.x),
	static_cast<int>(region.size.y)
    };
    
    SDL_RenderCopyEx(renderer->GetSDLRenderer(), texture, &src, &dst, 0, nullptr, spriteFlip);
}

void SpriteComponent::SetTexture(SDL_Texture* texture) {
    this->texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    this->region = { 0, 0, (float) width, (float) height };
}
