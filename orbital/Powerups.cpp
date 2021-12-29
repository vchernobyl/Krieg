#include "Powerups.h"
#include "Collision.h"
#include "Player.h"
#include <SDL/SDL.h>

HealthPack::HealthPack(Game* game) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Heart.png");
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCollisionFilter(CollisionCategory::Default, CollisionCategory::Player);
}

void HealthPack::OnBeginContact(const Contact& contact) {
    SDL_Log("colliding");
    if (dynamic_cast<Player*>(contact.other)) {
        SetState(Actor::State::Dead);
    }
}
