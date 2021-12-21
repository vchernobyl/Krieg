#include "Orbit.h"

Orbit::Orbit(Game* game, const Vector2& center, float radius)
    : Actor(game), center(center), radius(radius) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

    auto rigidbody = new RigidbodyComponent(this, BodyType::Static);
    auto collider = new CircleColliderComponent(this, 0.5f * 1.5f);
    collider->SetCollisionFilter(CollisionCategory::Enemy);

    SetScale(1.5f);
    SetTag("Orbit");
}

void Orbit::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(center, radius, Vector4(1.0f, 1.0f, 0.0f, 0.5f));
}
