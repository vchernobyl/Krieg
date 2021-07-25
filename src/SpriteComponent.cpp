#include "Actor.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

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
    const auto size = region.size * Game::PixelsToUnits;
    const auto dst = Rectangle(owner->GetPosition(), size * owner->GetScale());

    auto effect = SpriteEffect::None;
    if (flipX) effect = static_cast<SpriteEffect>(effect | FlipHorizontally);
    if (flipY) effect = static_cast<SpriteEffect>(effect | FlipVertically);

    renderer->DrawTexture(texture, region, dst, 0, effect);
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->region = Rectangle(0.0f, 0.0f, texture->width, texture->height);
}
