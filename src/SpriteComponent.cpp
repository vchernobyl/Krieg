#include "Actor.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      texWidth(0),
      texHeight(0) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Renderer* renderer) {
    if (texture) {
	SDL_Rect dst;
	dst.w = static_cast<int>(texWidth * owner->GetScale());
	dst.h = static_cast<int>(texHeight * owner->GetScale());
	dst.x = static_cast<int>(owner->GetPosition().x);
	dst.y = static_cast<int>(owner->GetPosition().y);
	renderer->GetCamera()->ToScreenSpace(dst);
	renderer->DrawTexture(texture, &dst, flip);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture, SDL_RendererFlip flip) {
    this->texture = texture;
    this->flip = flip;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}
