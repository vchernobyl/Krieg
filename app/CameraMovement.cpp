#include "CameraMovement.h"
#include "InputSystem.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"
#include "Camera.h"

CameraMovement::CameraMovement(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
    camera = owner->GetGame()->GetMainCamera();
}

void CameraMovement::ProcessInput(const InputState& inputState) {
    const float mouseScroll = inputState.Mouse.GetScrollWheel().y;
    if (mouseScroll != 0.0f) {
        camera->SetScale(mouseScroll + camera->GetScale());
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_MIDDLE) == ButtonState::Pressed) {
        dragStart = camera->ScreenToWorld(inputState.Mouse.GetPosition());
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_MIDDLE) == ButtonState::Held) {
        dragEnd = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        Vector2 distance = dragEnd - dragStart;
        camera->SetPosition(camera->GetPosition() - distance);
    }
}
