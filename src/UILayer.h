#pragma once

#include <vector>

class Game;
class SpriteBatch;
class SpriteComponent;
class TextComponent;
struct InputState;

/* The problem with the approach where each UI layer contains sprites, texts etc is that these
will be automatically added to the renderer. This means that those sprites will be by default
rendered via the default sprite batch with the world space view, and not the screen space view.
Basically we have a sprite container which will be drawn in world space regardless if it is in the UI
layer or not. Somehow we have to separate drawables in the world space vs. drawables in the screen space
(UI). We can consider a potential approach:
    1. Each UI layer contains it's own drawables, which will NOT be part of the renderer.
    2. Every drawables will have two constructors - one given an actor/owner (as it is not), and another
    where the argument is the UI layer or some other thing.
*/

class UILayer {
public:
    enum class State {
        Active,
        Closing
    };
    
    UILayer(Game* game);
    virtual ~UILayer() {}
    
    virtual void Update(float deltaTime) {}
    virtual void Draw(SpriteBatch& batch);

    // TODO: Hook these up to the game input processing.
    virtual void ProcessInput(const InputState& inputState) {}
    virtual void HandleKeyPress(int key) {}

    State GetState() const { return state; }
    
private:
    Game* game;
    State state;

    // TODO: Probably should contain a list of all `Drawable` objects.
    std::vector<SpriteComponent*> sprites;
    std::vector<TextComponent*> texts;
};
