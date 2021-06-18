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

const float MoveVelocity = 200.0f;
const float JumpVelocity = 4000.0f;

Player::Player(Game* game) : Actor(game), direction(Vector2::Right) {
    SetPosition(Vector2(300, 700));
    SetScale(2.5f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/SpriteSheet.png"));
    sprite->SetDrawRegion(Rectangle(0, 0, 16, 16));

    rigidbody = new RigidbodyComponent(this, MotionType::PhysicsDriven);

    auto collider = new BoxColliderComponent(this);
    auto size = Vector2(16, 16) * GetScale();
    collider->SetBox(size.x, size.y);

    audio = new AudioComponent(this);

    particleProps.colorBegin = Vector4(255, 255, 255, 255);
    particleProps.colorEnd = Vector4(255 / 2, 255 / 2, 255 / 2, 0);

    particleProps.sizeBegin = 10.0f;
    particleProps.sizeEnd = 5.0f;
    particleProps.sizeVariation = 5.0f;

    particleProps.lifetime = 0.4f;

    particleProps.velocity = Vector2::Up * 50.0f;
    particleProps.velocityVariation = Vector2(130.0f, 20.0f);

    dustParticles = new ParticleEmitterComponent(this);
    dustParticles->SetTexture(game->GetRenderer()->GetTexture("assets/Particle.png"));
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
	audio->PlayEvent("event:/Jump");

	auto particlePosition = GetPosition();
	particlePosition.x += sprite->GetWidth() * GetScale() / 2;
	particlePosition.y += sprite->GetHeight() * GetScale() / 2; // Division by 2 only because sprite sheet contains 2 characters.
	particleProps.position = particlePosition;
	
	dustParticles->Emit(particleProps, 12);

	velocity.y = -JumpVelocity;
	isJumping = true;
    }

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
	audio->PlayEvent("event:/Shoot");
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
