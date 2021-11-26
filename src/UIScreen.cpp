#include "UIScreen.h"
#include "Game.h"
#include "SpriteBatch.h"
#include "SpriteComponent.h"
#include "Font.h"
#include "Actor.h"

UIScreen::UIScreen(Game* game)
    : Actor(game),
      state(State::Active) {
    game->PushUI(this);
    font = game->GetFont("data/fonts/Carlito-Regular.ttf");
}

void UIScreen::Draw(SpriteBatch& batch) {
    font->Draw(batch, "Hello World!", Vector2::Zero);
}

void UIScreen::ProcessInput(const struct InputState& input) {}
void UIScreen::HandleKeyPress(int key) {}
