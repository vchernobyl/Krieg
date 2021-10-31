#include "UIScreen.h"
#include "Texture.h"
#include "Font.h"
#include "Game.h"
#include "Renderer.h"

#include <cassert>

Button::Button(const std::string& name, class Font* font,
	       std::function<void()> onClick,
	       const Vector2& position, const Vector2& dimensions)
    : onClick(onClick),
      nameTexture(nullptr),
      font(font),
      position(position),
      dimensions(dimensions),
      highlighted(false) {
    SetName(name);
}

Button::~Button() {
    if (nameTexture) {
	nameTexture->Unload();
	delete nameTexture;
    }
}

void Button::SetName(const std::string& name) {
    this->name = name;

    if (nameTexture) {
	nameTexture->Unload();
	delete nameTexture;
	nameTexture = nullptr;
    }

    nameTexture = font->RenderText(name);
}

bool Button::ContainsPoint(const Vector2& point) const {
    if (point.x < (position.x - dimensions.x / 2.0f) ||
	point.x > (position.x + dimensions.x / 2.0f) ||
	point.y < (position.y - dimensions.y / 2.0f) ||
	point.y > (position.y + dimensions.y / 2.0f)) {
	return false;
    }
    return true;
}

void Button::OnClick() {
    if (onClick) {
	onClick();
    }
}

UIScreen::UIScreen(Game* game)
    : game(game),
      title(nullptr),
      background(nullptr),
      titlePosition(0.0f, 300.0f),
      nextButtonPosition(0.0f, 200.0f),
      backgroundPosition(0.0f, 250.0f),
      state(UIState::Active) {
    game->PushUI(this);
    font = game->GetFont("data/fonts/Carlito-Regular.ttf");
    buttonOn = game->GetRenderer()->GetTexture("data/textures/ButtonYellow.png");
    buttonOff = game->GetRenderer()->GetTexture("data/textures/ButtonBlue.png");
}

UIScreen::~UIScreen() {
    if (title) {
	title->Unload();
	delete title;
    }

    for (auto b : buttons) {
	delete b;
    }

    buttons.clear();
}

void UIScreen::Draw(SpriteBatch& spriteBatch) {
    if (background) {
	DrawTexture(spriteBatch, background, backgroundPosition);
    }
    // TODO: Finish
    assert(false);
}

void UIScreen::ProcessInput(const InputState& inputState) {
    assert(false); // not implemented yet.
}

void UIScreen::HandleKeyPress(int key) {
    assert(false); // not implemented yet.
}

void UIScreen::SetTitle(const std::string& text, const Vector4& color, int pointSize) {
    if (title) {
	title->Unload();
	delete title;
	title = nullptr;
    }

    title = font->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick) {
    assert(false); // not implemented yet.
}

void UIScreen::DrawTexture(SpriteBatch& spriteBatch, Texture* texture,
			   const Vector2& offset, float scale) {
    assert(false); // not implemented yet.
}

void UIScreen::SetRelativeMouseMode(bool relative) {
    assert(false); // not implemented yet.
}
