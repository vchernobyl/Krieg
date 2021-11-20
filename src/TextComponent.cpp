#include "TextComponent.h"
#include "Actor.h"
#include "Font.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteBatch.h"

TextComponent::TextComponent(Actor* owner, int drawOrder) : Component(owner, drawOrder) {
    owner->GetGame()->GetRenderer()->AddText(this);
}

TextComponent::~TextComponent() {
    owner->GetGame()->GetRenderer()->RemoveText(this);
}

void TextComponent::Draw(SpriteBatch& spriteBatch) {
    if (font) {
        font->Draw(spriteBatch, text, owner->GetPosition(), owner->GetScale(), updateOrder);
    }
}
