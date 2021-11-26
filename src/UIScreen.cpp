#include "UIScreen.h"
#include "Game.h"
#include "SpriteBatch.h"
#include "SpriteComponent.h"
#include "Font.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"

Button::Button(const std::string& text, class Font*,
               std::function<void()> onClick,
               const Vector2& position, const Vector2& size)
    : text(text),
      font(font),
      onClick(onClick),
      position(position),
      size(size),
      highlighted(false) {
}

bool Button::ContainsPoint(const Vector2& point) const {
    return point.x >= (position.x - size.x / 2.0f) &&
        point.x <= (position.x + size.x / 2.0f) &&
        point.y >= (position.y - size.y / 2.0f) &&
        point.y <= (position.y + size.y / 2.0f);
}

UIScreen::UIScreen(Game* game)
    : Actor(game),
      state(State::Active) {
    game->PushUI(this);
    font = game->GetFont("data/fonts/Carlito-Regular.ttf");
    buttonOn = game->GetRenderer()->GetTexture("data/textures/ButtonYellow.png");
    buttonOff = game->GetRenderer()->GetTexture("data/textures/ButtonBlue.png");
}

UIScreen::~UIScreen() {
    for (auto button : buttons) {
        delete button;
    }
}

void UIScreen::Draw(SpriteBatch& batch) {
    for (auto button : buttons) {
        // TODO: Currently UI is rendered via the text shader, which is not handling texture correctly.
        // This needs to be fixed somehow.
        // auto position = button->GetPosition();
        // auto size = button->GetSize();
        // auto dest = Vector4(position.x, position.y, size.x / 64.0f, size.y / 64.0f);
        // batch.Draw(dest, Vector4(0.0f, 0.0f, 1.0f, 1.0f), buttonOn->GetID(), 0, Color::White);
        auto alpha = button->GetHighlighted() ? 0.5f : 1.0f;
        auto color = Vector4(1.0f, 1.0f, 1.0f, alpha);
        font->Draw(batch, button->GetText(), button->GetPosition(), color);
    }
}

void UIScreen::ProcessInput(const struct InputState& input) {}

void UIScreen::HandleKeyPress(int key) {}

void UIScreen::AddButton(const std::string& text, const Vector2& position,
                         std::function<void()> onClick) {
    auto size = Vector2(static_cast<float>(buttonOn->GetWidth()),
                        static_cast<float>(buttonOn->GetHeight()));
    auto button = new Button(text, font, onClick, position, size);
    buttons.push_back(button);
}
