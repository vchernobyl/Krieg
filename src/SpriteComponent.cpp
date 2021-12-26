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
        float width = rect.z / pixelsPerUnit * owner->GetScale();
        float height = rect.w / pixelsPerUnit * owner->GetScale();

        auto position = owner->GetPosition();
        auto dest = Vector4(position.x - width / 2.0f, position.y - height / 2.0f, width, height);

        auto uv = Vector4(rect.x / texture->GetWidth(),
                          rect.y / texture->GetHeight(),
                          rect.z / texture->GetWidth(),
                          rect.w / texture->GetHeight());

        spriteBatch.Draw(dest, uv, texture->GetID(), drawOrder, color, owner->GetRotation());
    }
}

Vector2 SpriteComponent::GetSize() const {
    return Vector2(texture->GetWidth(), texture->GetHeight());
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->rect = Vector4(0.0f, 0.0f, texture->GetWidth(), texture->GetHeight());
}

void SpriteComponent::SetRect(int x, int y, int width, int height) {
    rect.x = x;
    rect.y = y;
    rect.z = width;
    rect.w = height;
}
