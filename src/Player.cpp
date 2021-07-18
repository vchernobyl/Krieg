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

const float MaxVelocity = 8.0f;
const float Acceleration = 30.0f;
const float Deceleration = 5.0f;

Player::Player(Game* game) : Actor(game) {
    SetPosition(Vector2(5, 10));
    SetScale(2.0f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Player.png"));

    auto collider = new BoxColliderComponent(this);
    auto size = sprite->GetSize() * GetScale();
    collider->SetBox(size.x, size.y);

    rigidbody = collider->GetAttachedRigidbody();
}

void Player::ActorInput(const InputState& inputState) {
    velocity = rigidbody->GetVelocity();
    float force = 0.0f;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) {
	if (velocity.x < MaxVelocity) force = Acceleration;
	sprite->flipX = false;
    } else if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) {
	if (velocity.x > -MaxVelocity) force = -Acceleration;
	sprite->flipX = true;
    } else {
	force = velocity.x * -Deceleration;
    }

    rigidbody->ApplyForce(Vector2(force, 0.0f));
}

void Player::UpdateActor(float deltaTime) {
    GetGame()->GetRenderer()->GetCamera()->CenterAt(GetPosition());
}
