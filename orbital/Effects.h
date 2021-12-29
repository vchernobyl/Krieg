#pragma once

#include <Engine.h>

class Explosion : public Actor {
public:
    Explosion(Game* game, const Vector2& position, float lifeTime = 1.0f);
};

class HeartPickup : public Actor {
public:
    HeartPickup(Game* game, const Vector2& position, float lifeTime = 1.0f);
};
