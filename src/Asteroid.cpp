#include "Asteroid.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Random.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game) {
    Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f),
					Vector2(512.0f, 384.0f));

    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

    MoveComponent* movement = new MoveComponent(this);
    movement->SetForwardSpeed(150.0f);

    game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
    GetGame()->RemoveAsteroid(this);
}
