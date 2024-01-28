#include "Drone.h"
#include "Rocket.h"
#include "Player.h"
#include "Effects.h"
#include "Health.h"
#include "Collision.h"
#include "Timer.h"
#include "Powerups.h"
#include <cassert>

Drone::Drone(Game* game, const Vector2& movement)
	: Actor(game), movement(movement) {
	auto sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));
	sprite->SetColor(Color::Red);

	SetScale(0.75f);
	SetRotation(Math::Atan2(movement.y, movement.x));

	auto rigidbody = new RigidbodyComponent(this);
	rigidbody->SetVelocity(movement * 2.5f);

	auto health = new Health(this, 1);

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

		self->Start(shotInterval);
		});
}

Drone::~Drone() {
	new Explosion(GetGame(), GetPosition());

	auto chance = Random::GetFloat();
	if (chance <= 0.3f) {
		auto velocity = GetComponent<RigidbodyComponent>()->GetVelocity();
		auto heart = new Heart(GetGame(), velocity);
		heart->SetPosition(GetPosition());
	}
}

void Drone::UpdateActor(float deltaTime) {
	auto radius = collider->GetRadius();
	auto position = GetPosition() - Vector2(radius, radius);
	auto size = Vector2(radius, radius) * 2.0f;
	auto camera = GetGame()->GetMainCamera();

	if (!camera->IsBoxInView(position, size)) {
		Destroy();
	}
}

void Drone::OnBeginContact(const Contact& contact) {
	if (auto player = dynamic_cast<Player*>(contact.other)) {
		Destroy();
		auto health = player->GetComponent<Health>();
		assert(health);
		health->ReceiveDamage(50);
	}
}
