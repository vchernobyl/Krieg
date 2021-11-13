#include "Turret.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "AudioComponent.h"
#include "Ship.h"
#include "Damageable.h"
#include "InputSystem.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "DebugRenderer.h"

Bullet::Bullet(Game* game) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Bullet.png");
    sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    SetScale(0.35f);

    rigidbody = new RigidbodyComponent(this);
    rigidbody->SetFixedRotation(false);
    rigidbody->SetBullet(true);

    collider = new BoxColliderComponent(this, Vector2(1.0f, 0.125f) * GetScale());
    collider->SetSensor(true);
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Enemy |
                                 CollisionCategory::Ground);

}

void Bullet::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= lifeTime) {
        SetState(State::Dead);
    }
}

void Bullet::OnBeginContact(const struct Contact& contact) {
    if (dynamic_cast<Ship*>(contact.other)) return;

    SetState(State::Dead);
}

void Bullet::ShootAt(const Vector2& position, float speed) {
    auto direction = position - GetPosition();
    direction.Normalize();

    auto rotation = Math::Atan2(direction.y, direction.x);
    SetRotation(rotation);

    rigidbody->SetVelocity(direction * speed);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Laser_Shot");
}

Turret::Turret(Game* game) : Actor(game) {
}

void Turret::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(GetPosition(), 0.1f, Color::Red);

    timeBetweenShots += deltaTime;

    if (!isActivated || targets.empty()) return;

    if (timeBetweenShots >= 1.0f / fireRate) {
        timeBetweenShots = 0.0f;
        auto bullet = new Bullet(GetGame());
        bullet->SetPosition(GetPosition());
        bullet->ShootAt(targets[currentTargetIndex]->GetOwner()->GetPosition());
        currentTargetIndex = (currentTargetIndex + 1) % targets.size();
    }
}

void Turret::ActorInput(const InputState& inputState) {
    if (!isActivated) return;

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto camera = GetGame()->GetMainCamera();
        auto worldPoint = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        auto physics = GetGame()->GetPhysicsWorld();

        if (auto rigidbody = physics->GetRigidbodyAt(worldPoint)) {
            if (auto target = rigidbody->GetOwner()->GetComponent<Damageable>()) {
                if (IsTargeted(target)) {
                    target->Deselect();
                    RemoveTarget(target);
                } else if (targets.size() < stacks) {
                    target->Select();
                    AddTarget(target);
                    target->SetOnDestroy([this](Damageable* target) { RemoveTarget(target); });
                }
            }
        }
    }
}

void Turret::AddTarget(Damageable* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter == targets.end()) {
        targets.push_back(target);
    }
}

void Turret::RemoveTarget(Damageable* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter != targets.end()) {
        targets.erase(iter);
    }
}

bool Turret::IsTargeted(Damageable* target) const {
    auto iter = std::find(targets.begin(), targets.end(), target);
    return iter != targets.end();
}
