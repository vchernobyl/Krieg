#include "UILayer.h"
#include "Game.h"
#include "SpriteBatch.h"
#include "SpriteComponent.h"
#include "Font.h"
#include "Actor.h"
#include <algorithm>

UILayer::UILayer(Game* game)
    : Actor(game),
      state(State::Active) {
}

void UILayer::Draw(SpriteBatch& batch) {
}
