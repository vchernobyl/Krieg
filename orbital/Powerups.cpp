#include "Powerups.h"
#include "Collision.h"
#include "Player.h"
#include "Health.h"

Heart::Heart(Game* game) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Heart.png");
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCategoryAndMask(CollisionMask::Powerup, CollisionMask::Player);
    collider->SetSensor(true);
    collider->GetAttachedRigidbody()->SetVelocity(Vector2::One);
}

void Heart::OnBeginContact(const Contact& contact) {
    if (auto health = contact.other->GetComponent<Health>()) {
	health->AddHealth(HealingAmount);
	SetState(Actor::State::Dead);
    }
}
