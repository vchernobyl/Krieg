#include "SpriteComponent.h"
#include "SpriteBatch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : DrawableComponent(owner, drawOrder) {}

void SpriteComponent::Draw(SpriteBatch& spriteBatch) {
    if (texture) {
        const float pixelsPerUnit = 64.0f;
        float width = textureWidth / pixelsPerUnit * owner->GetScale();
        float height = textureHeight / pixelsPerUnit * owner->GetScale();

        auto position = owner->GetPosition();
        auto dest = Vector4(position.x - width / 2.0f, position.y - height / 2.0f, width, height);
        auto uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(dest, uv, texture->GetID(), drawOrder, color, owner->GetRotation());
    }
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->textureWidth = texture->GetWidth();
    this->textureHeight = texture->GetHeight();
}
