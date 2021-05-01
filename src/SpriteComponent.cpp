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
    if (texture) {
	SDL_Rect dst;
	dst.w = static_cast<int>(region.w * owner->GetScale());
	dst.h = static_cast<int>(region.h * owner->GetScale());
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

	renderer->DrawTexture(texture, &region, &dst, spriteFlip);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture, SDL_RendererFlip flip) {
    this->texture = texture;
    this->flip = flip;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    this->region = { 0, 0, width, height };
}
