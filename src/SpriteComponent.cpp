#include "Actor.h"
#include "SpriteComponent.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      texWidth(0),
      texHeight(0) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
    camera = owner->GetGame()->GetRenderer()->GetCamera();
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (texture) {
	Vector2 camPos = camera->GetPosition();
	SDL_Rect rect;
	rect.w = static_cast<int>(texWidth * owner->GetScale());
	rect.h = static_cast<int>(texHeight * owner->GetScale());
	rect.x = static_cast<int>(owner->GetPosition().x - camPos.x);
	rect.y = static_cast<int>(owner->GetPosition().y - camPos.y);
	SDL_RenderCopyEx(renderer, texture, nullptr, &rect, -Math::ToDegrees(owner->GetRotation()), nullptr, flip);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture, SDL_RendererFlip flip) {
    this->texture = texture;
    this->flip = flip;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}
