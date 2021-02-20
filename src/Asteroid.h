#pragma once

#include "Actor.h"

class Asteroid : public Actor {
public:
    Asteroid(class Game* game);
    ~Asteroid();
    class CircleComponent* GetCircle() const { return circle; }
private:
    class CircleComponent* circle;
};
