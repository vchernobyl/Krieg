#include "SpriteComponent.h"
#include "SpriteBatch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      textureWidth(0),
      textureHeight(0) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(SpriteBatch& spriteBatch) {
    if (texture) {
	float smallest = textureWidth < textureHeight ? textureWidth : textureHeight;
	Vector2 position = owner->GetPosition();
	float width = textureWidth / smallest;
	float height = textureHeight / smallest;
	Vector4 dest(position.x - width / 2.0f, position.y - height / 2.0f, width, height);
	Vector4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.Draw(dest, uv, texture->GetID(), 1.0f, Color::White, owner->GetRotation());
    }
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->textureWidth = texture->GetWidth();
    this->textureHeight = texture->GetHeight();
}
