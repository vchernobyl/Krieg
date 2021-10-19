#include "CameraComponent.h"
#include "InputSystem.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
}

void CameraComponent::ProcessInput(const InputState& inputState) {
    auto renderer = owner->GetGame()->GetRenderer();

    if (auto scroll = inputState.Mouse.GetScrollWheel(); scroll.y != 0.0f) {
	renderer->SetScale(renderer->GetScale() + scroll.y);

	auto view = Matrix4::CreateScale(renderer->GetScale());
	view *= Matrix4::CreateOrtho(renderer->GetScreenWidth(), renderer->GetScreenHeight(), 0.5f, 100.0f);
	SetViewMatrix(view);
    }

    const float camSpeed = 10.0f;
    if (inputState.Keyboard.IsKeyPressed(SDL_SCANCODE_W)) position.y += camSpeed;
    if (inputState.Keyboard.IsKeyPressed(SDL_SCANCODE_S)) position.y -= camSpeed;
    if (inputState.Keyboard.IsKeyPressed(SDL_SCANCODE_A)) position.x -= camSpeed;
    if (inputState.Keyboard.IsKeyPressed(SDL_SCANCODE_D)) position.x += camSpeed;

    auto view = Matrix4::CreateScale(renderer->GetScale());
    view *= Matrix4::CreateTranslation(Vector3(-position.x, -position.y, 0.0f));
    view *= Matrix4::CreateOrtho(renderer->GetScreenWidth(), renderer->GetScreenHeight(), 0.5f, 100.0f);
    SetViewMatrix(view);
}

void CameraComponent::Update(float deltaTime) {
    
}

void CameraComponent::SetViewMatrix(const Matrix4& view) {
    Game* game = owner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
}
