#include "UILayer.h"
#include "Game.h"
#include "SpriteBatch.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Actor.h"

UILayer::UILayer(Game* game)
    : game(game),
      state(State::Active) {
    auto owner = new Actor(game);
    auto sprite = new SpriteComponent(owner);
}

void UILayer::Draw(SpriteBatch& batch) {
    for (auto sprite : sprites) {
        sprite->Draw(batch);
    }

    for (auto text : texts) {
        text->Draw(batch);
    }
}
