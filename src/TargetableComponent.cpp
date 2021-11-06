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

        // There is another way to know if an actor has been clicked on.
        // We could use sprite bounds, but then the selectable area would be larger than the
        // body and wouldn't be as precise. For now this is working pretty good though.
        if (selectedRigidbody == owner->GetComponent<RigidbodyComponent>()) {
            isSelected = !isSelected;
            sprite->SetEnabled(isSelected);
            if (isSelected) {
                owner->SetTag("Target");
            } else {
                owner->SetTag("");
            }
        }
    }
}
