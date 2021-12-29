#include "Powerups.h"
#include "Collision.h"
#include "Player.h"
#include "Health.h"
#include "Effects.h"

Heart::Heart(Game* game, const Vector2& direction) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Heart.png");
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCategoryAndMask(CollisionMask::Powerup, CollisionMask::Player);
    collider->SetSensor(true);
    collider->GetAttachedRigidbody()->SetVelocity(direction);
}

void Heart::OnBeginContact(const Contact& contact) {
    if (auto health = contact.other->GetComponent<Health>()) {
        health->AddHealth(HealingAmount);

        new HeartPickup(GetGame(), GetPosition(), 0.7f);

        Destroy();
    }
}
