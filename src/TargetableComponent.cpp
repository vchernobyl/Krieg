#include "TargetableComponent.h"
#include "Actor.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "InputSystem.h"
#include "Game.h"
#include "PhysicsWorld.h"
#include "Camera.h"

TargetableComponent::TargetableComponent(Actor* owner) : Component(owner) {
    sprite = new SpriteComponent(owner, 300);
    sprite->SetTexture(owner->GetGame()->GetRenderer()->GetTexture("data/textures/Circle.png"));
    sprite->SetEnabled(false);
}

void TargetableComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto camera = owner->GetGame()->GetMainCamera();
        auto worldPoint = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        auto selectedRigidbody = owner->GetGame()->GetPhysicsWorld()->GetRigidbodyAt(worldPoint);

        // TODO: There has got to be a better way to know if an actor has been clicked on.
        if (selectedRigidbody == owner->GetComponent<RigidbodyComponent>()) {
            isSelected = !isSelected;
            sprite->SetEnabled(isSelected);
        }
    }
}
