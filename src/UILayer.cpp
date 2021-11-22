#include "UILayer.h"
#include "Game.h"

UILayer::UILayer(Game* game)
    : game(game),
      state(State::Active) {}
