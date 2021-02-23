#include "Actor.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      texWidth(0),
      texHeight(0) {
    owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (texture) {
	SDL_Rect rect;
	rect.w = static_cast<int>(texWidth * owner->GetScale());
	rect.h = static_cast<int>(texHeight * owner->GetScale());
	rect.x = static_cast<int>(owner->GetPosition().x - rect.w / 2);
	rect.y = static_cast<int>(owner->GetPosition().y - rect.h / 2);
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, -Math::ToDegrees(owner->GetRotation()), nullptr, flip);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture, SDL_RendererFlip flip) {
    this->texture = texture;
    this->flip = flip;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}
