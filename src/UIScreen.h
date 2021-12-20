#pragma once

#include "Maths.h"
#include <vector>
#include <string>
#include <functional>

class Game;
class SpriteBatch;
class SpriteComponent;
class TextComponent;
struct InputState;

class Button {
public:
    Button(const std::string& text, class Font*,
           std::function<void()> onClick,
           const Vector2& position, const Vector2& size);

    void SetText(const std::string& text) { this->text = text; }
    const std::string& GetText() const { return text; }
    
    const Vector2& GetPosition() const { return position; }
    const Vector2& GetSize() const { return size; }
    
    void SetHighlighted(bool flag) { highlighted = flag; }
    bool GetHighlighted() const { return highlighted; }

    bool ContainsPoint(const Vector2& point) const;
    void OnClick() { if (onClick) onClick(); }

private:
    std::string text;
    class Font* font;
    std::function<void()> onClick;
    Vector2 position;
    Vector2 size;
    bool highlighted;
};

class UIScreen {
public:
    enum class State {
        Active,
        Closing
    };
    
    UIScreen(Game* game);
    virtual ~UIScreen();
    
    virtual void Update(float deltaTime) {}
    virtual void Draw(SpriteBatch& batch);
    virtual void ProcessInput(const struct InputState& input);
    virtual void HandleKeyPress(int key);

    void Close();

    State GetState() const { return state; }

    void SetTitle(const std::string& text,
                  const Vector4& color = Color::White,
                  int pointSize = 48);

    void AddButton(const std::string& text,
                   const Vector2& position = Vector2::Zero,
                   std::function<void()> onClick = nullptr);

protected:
    void DrawTexture(class SpriteBatch& batch, class Texture* texture,
                     const Vector2& offset = Vector2::Zero,
                     float scale = 1.0f,
                     bool flipY = false);
    void SetRelativeMouseMode(bool flag);

    class Game* game;
    class Font* font;

    Vector2 titlePosition;
    Vector2 backgroundPosition;

    State state;
    std::vector<Button*> buttons;

    // Game specific, remove later.
    class Texture* title;
    class Texture* background;
    class Texture* buttonOn;
    class Texture* buttonOff;
};
