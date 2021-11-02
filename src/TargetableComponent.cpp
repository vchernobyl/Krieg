#include "TargetableComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "InputSystem.h"
#include "Game.h"

TargetableComponent::TargetableComponent(Actor* owner) : Component(owner) {
    sprite = new SpriteComponent(owner, 300);
    sprite->SetTexture(owner->GetGame()->GetRenderer()->GetTexture("data/textures/Circle.png"));
    sprite->SetEnabled(false);
}

void TargetableComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        isSelected = !isSelected;
        sprite->SetEnabled(isSelected);
    }
}
