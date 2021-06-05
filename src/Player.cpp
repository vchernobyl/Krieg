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
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/EffectsSpriteSheet.png"));
    sprite->SetDrawRegion(Rectangle(0, 0, 16, 16));
}

void MuzzleFlash::UpdateActor(float deltaTime) {
    if (frames > 0) { Destroy(); }
    frames++;
}

Bullet::Bullet(Game* game, const Vector2& direction) : Actor(game) {
    SetScale(0.75f);

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Bullet.png"));

    if (direction == Vector2::Left) {
	sprite->flipX = true;
    }

    rigidbody = new RigidbodyComponent(this);

    float spreadRange = 0.7f;
    auto spread = Vector2(0.0f, Random::GetFloatRange(-spreadRange, spreadRange));
    rigidbody->velocity = (direction * 10.0f) + spread;

    collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(sprite->GetWidth(), sprite->GetHeight()) * GetScale());

    particleProps.colorBegin = Vector4(255, 255, 0, 255);
    particleProps.colorEnd = Vector4(255, 56, 0, 0);

    particleProps.sizeBegin = 10.0f;
    particleProps.sizeEnd = 3.0f;
    particleProps.sizeVariation = 2.0f;
    
    particleProps.lifetime = 0.3f;
    
    particleProps.velocity.x = -Math::Sign(rigidbody->velocity.x) * 80.0f;
    particleProps.velocityVariation = Vector2(50.0f, 150.0f);
}

void Bullet::OnCollisionEnter(const CollisionInfo& info) {
    auto emitter = new Actor(GetGame());
    auto sparkParticles = new ParticleEmitterComponent(emitter);
    sparkParticles->SetTexture(GetGame()->GetRenderer()->GetTexture("assets/Particle.png"));
    sparkParticles->SetOnEmissionEnd([=]() { emitter->Destroy(); });

    particleProps.position = GetPosition();
    sparkParticles->Emit(particleProps, 12);

    rigidbody->velocity = Vector2::Zero;

    Destroy();
}

const float MoveVelocity = 200.0f;
const float JumpVelocity = 450.0f;

Player::Player(Game* game) : Actor(game), direction(Vector2::Right) {
    SetPosition(Vector2(300, 700));
    SetScale(2.5f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/SpriteSheet.png"));
    sprite->SetDrawRegion(Rectangle(0, 0, 16, 16));

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(16, 16) * GetScale());

    rigidbody = new RigidbodyComponent(this);

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
	auto bullet = new Bullet(GetGame(), direction);
	auto muzzleFlash = new MuzzleFlash(GetGame());
	
	if (direction == Vector2::Right) {
	    auto bulletOffset = Vector2(16 * GetScale() + 8, 12);
	    bullet->SetPosition(GetPosition() + bulletOffset);

	    auto muzzleOffset = Vector2(32, (16 * GetScale() / 2) - (16 * muzzleFlash->GetScale() / 2));
	    muzzleOffset.y -= 3;
	    muzzleFlash->SetPosition(GetPosition() + muzzleOffset);
	} else {
	    auto bulletOffset = Vector2(-16 * GetScale(), 12);
	    bullet->SetPosition(GetPosition() + bulletOffset);
	    
	    auto muzzleOffset = Vector2(-32, (16 * GetScale() / 2) - (16 * muzzleFlash->GetScale() / 2));
	    muzzleOffset.y -= 3;
	    muzzleFlash->SetPosition(GetPosition() + muzzleOffset);
	}

	audio->PlayEvent("event:/Shoot");
    }
}

void Player::UpdateActor(float deltaTime) {
    rigidbody->velocity.x = velocity.x * deltaTime;
    rigidbody->velocity.y += velocity.y * deltaTime;

    if (isJumping && Math::NearZero(rigidbody->velocity.y)) {
	isJumping = false;
    }

    GetGame()->GetRenderer()->GetCamera()->Follow(this);
}
