#include "Planet.h"
#include "Rocket.h"
#include "Player.h"
#include "Drone.h"
#include "Collision.h"

Planet::Planet(Game* game, const Vector2& center, float radius)
    : Actor(game), center(center), radius(radius) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

    auto rigidbody = new RigidbodyComponent(this, BodyType::Static);
    auto collider = new CircleColliderComponent(this, 0.5f * 1.5f);
    collider->SetCategoryAndMask(CollisionMask::Enemy, CollisionMask::PlayerProjectile);

    rocketSound = new AudioComponent(this);

    SetScale(1.5f);
    SetTag("Planet");
}

void Planet::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(center, radius, Vector4(1.0f, 1.0f, 0.0f, 0.5f));

    droneSpawnTime += deltaTime;
    if (droneCount < maxDrones && droneSpawnTime >= droneSpawnInterval) {
        droneSpawnTime = 0.0f;
        droneCount++;

	auto direction = Random::GetVector(-Vector2::One, Vector2::One);
	direction.Normalize();
        new Drone(GetGame(), direction, [&]() { droneCount--; });
    }
}
