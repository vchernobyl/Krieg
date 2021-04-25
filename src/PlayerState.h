#pragma once

class Player;
class InputState;

class PlayerState {
public:
    virtual ~PlayerState() {}
    virtual PlayerState* ProcessInput(Player& player, const InputState& input) { return nullptr; }
    virtual PlayerState* Update(Player& player) { return nullptr; }
    virtual void Enter(Player& player) {}
};
