#include "Asteroid.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Random.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "RigidbodyComponent.h"
#include "CircleColliderComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game) {
    Vector2 randPos = Random::GetVector(Vector2(-8.0f, -6.0f),
					Vector2(8.0f, 6.0f));

    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

//    MoveComponent* movement = new MoveComponent(this);
//    movement->SetForwardSpeed(1.8f);

    game->AddAsteroid(this);

    new RigidbodyComponent(this);
    new CircleColliderComponent(this, Vector2(0.0f, 0.0f), 0.5f);
}

Asteroid::~Asteroid() {
    GetGame()->RemoveAsteroid(this);
}
