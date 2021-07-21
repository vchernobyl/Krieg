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

MuzzleFlash::MuzzleFlash(Game* game) : Actor(game) {
    SetScale(2.0f);
    
    auto sprite = new SpriteComponent(this, 200);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Muzzle.png"));
}

void MuzzleFlash::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= 0.015f) {
	Destroy();
    }
}

const float BulletSpeed = 30.0f;
const float SpreadVariation = 1.0f;

Bullet::Bullet(Game* game, Vector2 direction, Vector2 position) : Actor(game) {
    SetPosition(position);
    
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Bullet.png"));

    auto rigidbody = new RigidbodyComponent(this, MotionType::Dynamic);
    auto velocity = Vector2(direction.x * BulletSpeed, Random::GetFloatRange(-SpreadVariation, SpreadVariation));
    rigidbody->SetVelocity(velocity);
    rigidbody->SetGravityScale(0.0f);
    rigidbody->SetBullet(true);

    auto box = new BoxColliderComponent(this, sprite->GetSize());
    box->SetCollisionFilter(CollisionCategory::Bullet,
			    CollisionCategory::Ground | CollisionCategory::Enemy);
}

void Bullet::OnBeginContact() {
    Destroy();
}

const float MaxVelocity = 10.0f;
const float Acceleration = 27.5f;
const float Deceleration = 5.0f;
const float JumpImpulse = 17.0f;

Player::Player(Game* game) : Actor(game), direction(Vector2::Right) {
    SetPosition(Vector2(2, 20));
    SetScale(2.0f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Player.png"));

    auto size = sprite->GetSize() * GetScale();
    auto box = new BoxColliderComponent(this, size);
    box->SetCollisionFilter(CollisionCategory::Player, CollisionCategory::Ground);

    rigidbody = box->GetAttachedRigidbody();

    audio = new AudioComponent(this);
}

void Player::ActorInput(const InputState& inputState) {
    velocity = rigidbody->GetVelocity();
    float force = 0.0f;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) {
	if (velocity.x < MaxVelocity) force = Acceleration;
	sprite->flipX = false;
	direction = Vector2::Right;
    } else if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) {
	if (velocity.x > -MaxVelocity) force = -Acceleration;
	sprite->flipX = true;
	direction = Vector2::Left;
    } else {
	force = velocity.x * -Deceleration;
    }

    rigidbody->ApplyForce(Vector2(force, 0.0f));

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_UP) == ButtonState::Pressed) {
	rigidbody->ApplyImpulse(Vector2::Up * rigidbody->GetMass() * JumpImpulse);
	audio->PlayEvent("event:/Jump");
    }

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
	auto offset = Vector2(0.75f, 0.25f);
	if (direction == Vector2::Left) {
	    offset = Vector2(-0.75f, 0.25f);
	}

	auto bullet = new Bullet(GetGame(), direction, GetPosition() + offset);
	auto flash = new MuzzleFlash(GetGame());
	flash->SetPosition(GetPosition() + Vector2(offset.x, 0.0f));
	
	audio->PlayEvent("event:/Shoot");
    }
}

void Player::UpdateActor(float deltaTime) {
    GetGame()->GetRenderer()->GetCamera()->CenterAt(GetPosition());
}
