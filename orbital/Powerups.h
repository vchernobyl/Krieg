#pragma once

#include <Engine.h>

class Heart : public Actor {
public:
    Heart(Game* game);
    void OnBeginContact(const Contact& contact) override;
private:
    static constexpr int HealingAmount = 50;
};
