#include "CameraComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
    const auto renderer = owner->GetGame()->GetRenderer();
    screenWidth = renderer->GetScreenWidth();
    screenHeight = renderer->GetScreenHeight();
    orthoProjection = Matrix4::CreateOrtho(screenWidth, screenHeight, 0.0f, 1.0f);
}

// TODO: This is gameplay code, needs to be pulled out of the camera component,
// and extracted into a separate camera movement component.
// Use `SetPosition(Vector2)` and `SetScale(float)` instead.
void CameraComponent::ProcessInput(const InputState& inputState) {
    const float mouseScroll = inputState.Mouse.GetScrollWheel().y;
    if (mouseScroll != 0.0f) {
        scale += mouseScroll;
        needsUpdate = true;
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_MIDDLE) == ButtonState::Pressed) {
        dragStart = ScreenToWorld(inputState.Mouse.GetPosition());
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_MIDDLE) == ButtonState::Held) {
        dragEnd = ScreenToWorld(inputState.Mouse.GetPosition());
        const Vector2 distance = dragEnd - dragStart;
        position -= distance;
        needsUpdate = true;
    }
}

void CameraComponent::Update(float deltaTime) {
    if (needsUpdate) {
        needsUpdate = false;

        // Looks like it's working correctly, but I'm not sure whether the
        // multiplication order is correct or just an accident.
        view = Matrix4::CreateTranslation(Vector3(-position.x, -position.y, 0.0f));
        view *= Matrix4::CreateScale(scale);
        view *= orthoProjection;

        const auto game = owner->GetGame();
        game->GetRenderer()->SetViewMatrix(view);
    }
}

Vector2 CameraComponent::ScreenToWorld(const Vector2& screenPoint) {
    // Invert the y coords.
    auto worldPoint = Vector2(screenPoint.x, screenHeight - screenPoint.y);

    // Make (0, 0) to be at the center of the screen.
    worldPoint -= Vector2(screenWidth / 2.0f, screenHeight / 2.0f);
    worldPoint /= scale;
    worldPoint += position;
    
    return worldPoint;
}
