#include "Turret.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

Bullet::Bullet(Game* game) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Bullet.png");
    sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    SetScale(0.5f);

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->SetFixedRotation(false);
    collider = new BoxColliderComponent(this, Vector2(0.125f, 1.0f) * GetScale()); 
}

Turret::Turret(Game* game) : Actor(game) {
}

void Turret::UpdateActor(float deltatime) {
}
