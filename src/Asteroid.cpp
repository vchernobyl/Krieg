#include "Asteroid.h"
#include "Game.h"
#include "Math.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
    : Actor(game),
      circle(nullptr) {
    Vector2 randPos = Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f, 768.0f));
    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("assets/Asteroid.png"));

    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(75.0f);

    circle = new CircleComponent(this);
    circle->SetRadius(40.0f);
}
