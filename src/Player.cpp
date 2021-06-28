#include "Player.h"
#include "Game.h"
#include "Renderer.h"
#include "Camera.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "ParticleEmitterComponent.h"
#include "AudioComponent.h"
#include "InputSystem.h"
#include "AudioSystem.h"
#include "Random.h"

const float MoveVelocity = 2.0f;
const float JumpVelocity = 4.0f;

Player::Player(Game* game) : Actor(game), direction(Vector2::Right) {
    SetPosition(Vector2(5, 10));

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Player.png"));

    rigidbody = new RigidbodyComponent(this, MotionType::PhysicsDriven);

    auto collider = new BoxColliderComponent(this);
    auto size = sprite->GetSize() * GetScale();
    collider->SetBox(size.x, size.y);

}

void Player::ActorInput(const InputState& inputState) {
    velocity = Vector2::Zero;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) {
	velocity.x = MoveVelocity;
	direction = Vector2::Right;
	sprite->flipX = false;
    }

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) {
	velocity.x = -MoveVelocity;
	direction = Vector2::Left;
	sprite->flipX = true;
    }

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_UP) == ButtonState::Pressed) {
	velocity.y = -JumpVelocity;
    }
}

void Player::UpdateActor(float deltaTime) {
    // BUG: The character movement will have a tiny "shaking" when moving. This only happens when the
    // velocity has a fractional component (e.g. 3.2f).
    // Math.Floor is only a temporary fix, will probably have to make some adjustemenets in the
    // Renderer in the future. The problem could probably lie in the float-to-int conversion, because
    // the Renderer accepts the SDL_Rect for position, which consists of 4 ints (x, y, w, h).
    float gravity = rigidbody->GetVelocity().y;
    auto v = Vector2(Math::Floor(velocity.x), gravity + Math::Floor(velocity.y));
    rigidbody->SetVelocity(v);

    if (isJumping && Math::NearZero(rigidbody->GetVelocity().y)) {
	isJumping = false;
    }

    GetGame()->GetRenderer()->GetCamera()->Follow(this);
}
