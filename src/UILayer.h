#pragma once

class Game;
class SpriteBatch;
struct InputState;

class UILayer {
public:
    enum class State {
        Active,
        Closing
    };
    
    UILayer(Game* game);
    virtual ~UILayer() {}
    virtual void Update(float deltaTime) {}
    virtual void Draw(SpriteBatch& spriteBatch) {}
    virtual void ProcessInput(const InputState& inputState) {}
    virtual void HandleKeyPress(int key) {}

    State GetState() const { return state; }
    
private:
    Game* game;
    State state;
};
