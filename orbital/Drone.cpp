#include "Drone.h"
#include "Rocket.h"
#include "Player.h"
#include "Explosion.h"
#include "Health.h"
#include "Collision.h"

Drone::Drone(Game* game, const Vector2& movement,
             std::function<void()> onDestroy)
    : Actor(game), movement(movement), onDestroy(onDestroy) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));
    sprite->SetColor(Color::Red);

    rocketSound = new AudioComponent(this);
    hitSound = new AudioComponent(this);

    SetScale(0.75f);
    SetRotation(Math::Atan2(movement.y, movement.x));

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->SetVelocity(movement * 2.5f);
    
    auto health = new Health(this, 1);
    health->SetOnReceiveDamage([this]() { hitSound->PlayEvent("event:/Laser_Hit"); });

    collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCategoryAndMask(CollisionMask::Enemy,
				 CollisionMask::Player | CollisionMask::PlayerProjectile);
}

Drone::~Drone() {
    if (onDestroy) onDestroy();
    new Explosion(GetGame(), GetPosition());
}

void Drone::UpdateActor(float deltaTime) {
    fireTimer += deltaTime;
    if (fireTimer >= fireRate) {
        fireTimer = 0.0f;
        auto player = dynamic_cast<Player*>(GetGame()->GetActorByTag("Player"));
        if (!player) return;

        auto direction = Vector2::Normalize(player->GetPosition() - GetPosition());
        auto rocket = new Rocket(GetGame());

        auto collider = rocket->GetComponent<ColliderComponent>();
	collider->SetCategoryAndMask(CollisionMask::EnemyProjectile, CollisionMask::Player);
        
        rocket->SetPosition(GetPosition());
        rocket->SetSpeed(500.0f);
        rocket->Launch(direction);

        rocketSound->PlayEvent("event:/Launch_Rocket");
    }

    auto radius = collider->GetRadius();
    auto position = GetPosition() - Vector2(radius, radius);
    auto size = Vector2(radius, radius) * 2.0f;
    auto camera = GetGame()->GetMainCamera();

    if (!camera->IsBoxInView(position, size)) {
        SetState(Actor::State::Dead);
    }
}

void Drone::OnBeginContact(const Contact& contact) {
    if (dynamic_cast<Player*>(contact.other)) {
        SetState(Actor::State::Dead);
    }
}
