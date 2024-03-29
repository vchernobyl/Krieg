#include "Asteroid.h"
#include "Actor.h"
#include "Game.h"
#include "Maths.h"
#include "Random.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "CircleColliderComponent.h"
#include "TargetComponent.h"
#include "HealthComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game) {
    SetPosition(Random::GetVector(Vector2(-8.0f, -6.0f), Vector2(8.0f, 6.0f)));
    SetScale(Random::GetFloatRange(0.35f, 0.75f));
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

    auto collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCollisionFilter(CollisionCategory::Ground);

    new TargetComponent(this);
    new HealthComponent(this, 150);
}
