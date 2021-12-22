#include "Drone.h"
#include "Rocket.h"
#include "Player.h"

Drone::Drone(Game* game, const Vector2& movement,
             std::function<void()> onDestroy)
    : Actor(game), movement(movement), onDestroy(onDestroy) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));
    sprite->SetColor(Color::Red);

    rocketSound = new AudioComponent(this);

    SetScale(0.75f);
    SetRotation(Math::Atan2(movement.y, movement.x));

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->SetVelocity(movement);
    
    auto collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCollisionFilter(CollisionCategory::Enemy, CollisionCategory::Player);
}

void Drone::UpdateActor(float deltaTime) {
    fireTimer += deltaTime;
    if (fireTimer >= 1.0f / fireRate) {
        fireTimer = 0.0f;
        auto player = dynamic_cast<Player*>(GetGame()->GetActorByTag("Player"));
        auto direction = Vector2::Normalize(player->GetPosition() - GetPosition());
        auto rocket = new Rocket(GetGame());
        
        rocket->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Player);
        rocket->SetPosition(GetPosition());
        rocket->SetSpeed(1000.0f);
        rocket->Launch(direction);

        rocketSound->PlayEvent("event:/Launch_Rocket");
    }
}

void Drone::OnBeginContact(const Contact& contact) {
    SetState(Actor::State::Dead);
    if (onDestroy) onDestroy();
}
