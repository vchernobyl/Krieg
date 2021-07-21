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

const float Bullet::Speed = 30.0f;
const float Bullet::SpreadVariation = 1.0f;

Bullet::Bullet(Game* game, Vector2 direction, Vector2 position) : Actor(game) {
    SetPosition(position);
    
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Bullet.png"));

    auto rigidbody = new RigidbodyComponent(this, MotionType::Dynamic);
    auto velocity = Vector2(direction.x * Speed, Random::GetFloatRange(-SpreadVariation, SpreadVariation));
    rigidbody->SetVelocity(velocity);
    rigidbody->SetGravityScale(0.0f);
    rigidbody->SetBullet(true);

    auto box = new BoxColliderComponent(this, sprite->GetSize());
    box->SetCollisionFilter(CollisionCategory::Bullet,
			    CollisionCategory::Ground | CollisionCategory::Enemy);
}

void Bullet::OnBeginContact(const Manifold& manifold) {
    Destroy();

    auto sparks = new Actor(GetGame());
    auto particles = new ParticleEmitterComponent(sparks);
    particles->SetTexture(GetGame()->GetRenderer()->GetTexture("assets/Particle.png"));
    particles->SetOnEmissionEnd([sparks]() { sparks->Destroy(); });

    ParticleProps props;
    props.position = GetPosition();
    props.velocity = Vector2(5.0f * manifold.contactNormal.x, 2.0f);
    props.velocityVariation = Vector2(2.0f, 2.0f);
    props.colorBegin = Vector4(255, 0, 0, 255);
    props.colorEnd = Vector4(255 / 2, 0, 0, 0);
    props.sizeBegin = 8.0f;
    props.sizeEnd = 2.5f;
    props.sizeVariation = 1.5f;
    props.rotationBegin = 0.0f;
    props.rotationSpeed = 1.0f;
    props.lifetime = 0.5f;

    particles->Emit(props, 20);
}

const float Player::MaxVelocity = 10.0f;
const float Player::Acceleration = 27.5f;
const float Player::Deceleration = 5.0f;
const float Player::JumpImpulse = 17.0f;

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
    
    particles = new ParticleEmitterComponent(this);
    particles->SetTexture(game->GetRenderer()->GetTexture("assets/Particle.png"));
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

	// TODO: Move particle props to the class level.
	ParticleProps props;
	props.position = GetPosition();
	props.position.y += 1.0f;
	props.position.x += 0.5f;
	props.velocity = rigidbody->GetVelocity() / 10;
	props.velocityVariation = Vector2(2.0f, 2.0f);
	props.colorBegin = Vector4(255, 255, 255, 255);
	props.colorEnd = Vector4(255 / 2, 255 / 2, 255 / 2, 0);
	props.sizeBegin = 5.0f;
	props.sizeEnd = 2.5f;
	props.sizeVariation = 1.5f;
	props.rotationBegin = 0.0f;
	props.rotationSpeed = 1.0f;
	props.lifetime = 0.5f;

	particles->Emit(props, 10);
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
