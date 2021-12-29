#include "Planet.h"
#include "Rocket.h"
#include "Player.h"
#include "Drone.h"

Planet::Planet(Game* game, const Vector2& center, float radius)
    : Actor(game), center(center), radius(radius) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Asteroid.png"));

    auto rigidbody = new RigidbodyComponent(this, BodyType::Static);
    auto collider = new CircleColliderComponent(this, 0.5f * 1.5f);
    collider->SetCollisionFilter(CollisionCategory::Enemy);

    rocketSound = new AudioComponent(this);

    SetScale(1.5f);
    SetTag("Planet");
}

void Planet::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(center, radius, Vector4(1.0f, 1.0f, 0.0f, 0.5f));

    auto player = dynamic_cast<Player*>(GetGame()->GetActorByTag("Player"));
    if (!player) return;
    
    auto direction = Vector2::Normalize(player->GetPosition() - GetPosition());

    time += deltaTime;
    if (time >= fireRate) {
        time = 0.0f;
        auto rocket = new Rocket(GetGame());
        auto collider = rocket->GetComponent<CircleColliderComponent>();
        collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Player);
        
        rocket->SetPosition(GetPosition());
        rocket->SetSpeed(500.0f);
        rocket->Launch(direction);

        rocketSound->PlayEvent("event:/Launch_Rocket");
    }

    droneSpawnTime += deltaTime;
    if (droneCount < maxDrones && droneSpawnTime >= droneSpawnInterval) {
        droneSpawnTime = 0.0f;
        droneCount++;

        new Drone(GetGame(), direction, [&]() { droneCount--; });
    }
}
