#pragma once

#include <Engine.h>

class HealthPack : public Actor {
public:
    HealthPack(Game* game);
    void OnBeginContact(const Contact& contact) override;
};
