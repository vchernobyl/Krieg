#pragma once

#include <Engine.h>

class Heart : public Actor {
public:
    Heart(Game* game, const Vector2& direction);
    void OnBeginContact(const Contact& contact) override;
private:
    static constexpr int HealingAmount = 50;
};
