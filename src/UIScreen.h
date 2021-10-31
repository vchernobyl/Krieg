#pragma once

#include "Math.h"
#include <string>
#include <functional>
#include <vector>

class Button {
public:
    Button(const std::string& name, class Font* font,
	   std::function<void()> onClick,
	   const Vector2& position, const Vector2& dimensions);
    ~Button();

    void SetName(const std::string& name);

    class Texture* GetNameTexture() { return nameTexture; }
    const Vector2& GetPosition() const { return position; }

    void SetHighlighted(bool flag) { highlighted = flag; }
    bool GetHighlighted() const { return highlighted; }

    bool ContainsPoint(const Vector2& point) const;
    void OnClick();

private:
    std::function<void()> onClick;
    std::string name;
    class Texture* nameTexture;
    class Font* font;
    Vector2 position;
    Vector2 dimensions;
    bool highlighted;
};

class UIScreen {
public:
    UIScreen(class Game* game);
    virtual ~UIScreen();

    virtual void Update(float deltaTime) {};
    virtual void Draw(class SpriteBatch& spriteBatch);
    virtual void ProcessInput(const struct InputState& inputState);
    virtual void HandleKeyPress(int key);

    enum class UIState {
	Active,
	Closing
    };

    void Close() { state = UIState::Closing; }
    UIState GetState() const { return state; }

    void SetTitle(const std::string& text,
		  const Vector4& color = Color::White,
		  int pointSize = 40);

    void AddButton(const std::string& name, std::function<void()> onClick);

protected:
    void DrawTexture(class SpriteBatch& spriteBatch,
		     class Texture* texture,
		     const Vector2& offset = Vector2::Zero,
		     float scale = 1.0f);
    void SetRelativeMouseMode(bool relative);

    class Game* game;
    class Font* font;
    class Texture* title;
    class Texture* background;
    class Texture* buttonOn;
    class Texture* buttonOff;

    Vector2 titlePosition;
    Vector2 nextButtonPosition;
    Vector2 backgroundPosition;

    UIState state;
    std::vector<Button*> buttons;
};
