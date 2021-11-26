#pragma once

#include "Actor.h"
#include "Math.h"
#include "Component.h"
#include <vector>
#include <string>
#include <functional>

class Game;
class SpriteBatch;
class SpriteComponent;
class TextComponent;
class UILayer;
struct InputState;

class Button {
public:
    Button(const std::string& name, class Font*,
           std::function<void()> onClick,
           const Vector2& position, const Vector2& size);
    ~Button();

    void SetText(const std::string& text);
    const Vector2& GetPosition() const { return position; }
    
    void SetHighlighted(bool flag) { highlighted = flag; }
    bool GetHighlighted() const { return highlighted; }

    bool ContainsPoint(const Vector2& point) const;
    void Onclick();

private:
    std::function<void()> onClick;
    std::string text;
    class Font* font;
    Vector2 position;
    Vector2 size;
    bool highlighted;
};

class UILayer : public Actor {
public:
    enum class State {
        Active,
        Closing
    };
    
    UILayer(Game* game);
    virtual ~UILayer() {}
    
    virtual void Update(float deltaTime) {}
    virtual void Draw(SpriteBatch& batch);

    State GetState() const { return state; }

private:
    Game* game;
    State state;
};
