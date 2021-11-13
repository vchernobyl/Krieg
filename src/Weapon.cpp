#include "Weapon.h"
#include "Game.h"
#include "Damageable.h"
#include "InputSystem.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "RigidbodyComponent.h"

Weapon::Weapon(Game* game) : Actor(game) {

}

void Weapon::UpdateActor(float deltaTime) {
    timeBetweenShots += deltaTime;

    if (!isActivated || targets.empty()) return;

    if (timeBetweenShots >= 1.0f / fireRate) {
        timeBetweenShots = 0.0f;
        Shoot();
        currentTargetIndex = (currentTargetIndex + 1) % targets.size();
    }
}

void Weapon::ActorInput(const InputState& inputState) {
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

void Weapon::AddTarget(Damageable* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter == targets.end()) {
        targets.push_back(target);
    }
}

void Weapon::RemoveTarget(Damageable* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter != targets.end()) {
        targets.erase(iter);
    }
}

bool Weapon::IsTargeted(Damageable* target) const {
    auto iter = std::find(targets.begin(), targets.end(), target);
    return iter != targets.end();
}
