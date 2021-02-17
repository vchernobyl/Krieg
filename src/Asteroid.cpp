#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Math.h"
#include "Random.h"

Asteroid::Asteroid(Game* game) : Actor(game) {
    Vector2 randPos = Random::GetVector(Vector2(0.0f, 0.0f), Vector2(1024.0f, 768.0f));
    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("assets/Asteroid.png"));

    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(75.0f);
}
