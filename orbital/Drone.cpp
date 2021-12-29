#include "Drone.h"
#include "Rocket.h"
#include "Player.h"
#include "Explosion.h"
#include "Health.h"
#include "Collision.h"
#include "Timer.h"

Drone::Drone(Game* game, const Vector2& movement)
    : Actor(game), movement(movement) {
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
    health->onDamage = [this]() { hitSound->PlayEvent("event:/Laser_Hit"); };

    collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCategoryAndMask(CollisionMask::Enemy,
				 CollisionMask::Player | CollisionMask::PlayerProjectile);

    float shotInterval = 1.35f;
    new Timer(this, shotInterval, [=](Timer* self) {
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

        self->Start(shotInterval);
    });
}

Drone::~Drone() {
    if (onDestroy) onDestroy();
    new Explosion(GetGame(), GetPosition());
}

void Drone::UpdateActor(float deltaTime) {
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
