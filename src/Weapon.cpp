#include "Weapon.h"
#include "Game.h"
#include "TargetComponent.h"
#include "InputSystem.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "RigidbodyComponent.h"
#include <cassert>

Weapon::Weapon(Game* game) : Actor(game) {
}

void Weapon::UpdateActor(float deltaTime) {
    timeBetweenShots += deltaTime;

    if (targets.empty()) return;

    if (timeBetweenShots >= 1.0f / fireRate) {
        timeBetweenShots = 0.0f;

        currentTargetIndex = currentTargetIndex % targets.size();

        assert(currentTargetIndex < targets.size());
        ShootAt(targets[currentTargetIndex]);

        currentTargetIndex++;
    }
}

void Weapon::ActorInput(const InputState& inputState) {
    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto camera = GetGame()->GetMainCamera();
        auto worldPoint = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        auto physics = GetGame()->GetPhysicsWorld();

        if (auto rigidbody = physics->GetRigidbodyAt(worldPoint)) {
            if (auto target = rigidbody->GetOwner()->GetComponent<TargetComponent>()) {
                if (IsTargeted(target)) {
                    target->Deselect();
                    RemoveTarget(target);
                } else if (targets.size() < stacks) {
                    target->Select();
                    AddTarget(target);
                    target->SetOnDestroy([this](TargetComponent* target) { RemoveTarget(target); });
                }
            }
        }
    }
}

void Weapon::AddTarget(TargetComponent* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter == targets.end()) {
        targets.push_back(target);
    }
}

void Weapon::RemoveTarget(TargetComponent* target) {
    auto iter = std::find(targets.begin(), targets.end(), target);
    if (iter != targets.end()) {
        targets.erase(iter);
    }
}

bool Weapon::IsTargeted(TargetComponent* target) const {
    auto iter = std::find(targets.begin(), targets.end(), target);
    return iter != targets.end();
}
