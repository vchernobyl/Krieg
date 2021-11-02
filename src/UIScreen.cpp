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

    if (title) {
        DrawTexture(spriteBatch, title, titlePosition);
    }

    for (auto b : buttons) {
        Texture* texture = b->GetHighlighted() ? buttonOn : buttonOff;
        DrawTexture(spriteBatch, texture, b->GetPosition());
        DrawTexture(spriteBatch, b->GetNameTexture(), b->GetPosition());
    }
}

void UIScreen::ProcessInput(const InputState& inputState) {
    if (!buttons.empty()) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
        mousePos.x -= game->GetRenderer()->GetScreenWidth() * 0.5f;
        mousePos.y -= game->GetRenderer()->GetScreenHeight() * 0.5f - mousePos.y;

        for (auto b : buttons) {
            if (b->ContainsPoint(mousePos)) {
                b->SetHighlighted(true);
            } else {
                b->SetHighlighted(false);
            }
        }
    }
}

void UIScreen::HandleKeyPress(int key) {
    switch (key) {
    case SDL_BUTTON_LEFT:
        if (!buttons.empty()) {
            for (auto b : buttons) {
                if (b->GetHighlighted()) {
                    b->OnClick();
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
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
    auto dims = Vector2(static_cast<float>(buttonOn->GetWidth()),
                        static_cast<float>(buttonOn->GetHeight()));
    auto button = new Button(name, font, onClick, nextButtonPosition, dims);
    buttons.emplace_back(button);
    nextButtonPosition.y -= buttonOff->GetHeight() + 20.0f;
}

void UIScreen::DrawTexture(SpriteBatch& spriteBatch, Texture* texture,
                           const Vector2& offset, float scale) {
    const float pixelsPerUnit = 64.0f;
    float width = texture->GetWidth() / pixelsPerUnit * scale;
    float height = texture->GetHeight() / pixelsPerUnit * scale;
    auto dest = Vector4(offset.x, offset.y, width, height);
    spriteBatch.Draw(dest, Vector4(0.0f, 0.0f, 1.0f, 1.0f), texture->GetID(), 0, Color::White);
}

void UIScreen::SetRelativeMouseMode(bool relative) {
    if (relative) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        // Make an initial call to get relative to clear out.
        SDL_GetRelativeMouseState(nullptr, nullptr);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}
