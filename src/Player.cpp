#include "Player.h"
#include "Game.h"
#include "Renderer.h"
#include "Camera.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "InputSystem.h"

Bullet::Bullet(Game* game) : Actor(game) {
    SetScale(0.75f);

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/Bullet.png"));

    rigidbody = new RigidbodyComponent(this);
    rigidbody->isKinematic = true;
    rigidbody->velocity.x = 10.0f;

    collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(sprite->GetWidth(), sprite->GetHeight()) * GetScale());
    collider->isTrigger = true;
}

void Bullet::OnCollisionEnter(const CollisionInfo& info) {
    if (!dynamic_cast<Player*>(info.other->GetOwner())) {
	Destroy();
    }
}

const float MoveVelocity = 200.0f;
const float JumpVelocity = 450.0f;

Player::Player(Game* game) : Actor(game) {
    SetPosition(Vector2(300, 700));
    SetScale(2.5f);

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/SpriteSheet.png"));
    sprite->SetRegion({ 0, 0, 16, 16});

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(16, 16) * GetScale());

    rigidbody = new RigidbodyComponent(this);
}

void Player::ActorInput(const InputState& inputState) {
    velocity = Vector2::Zero;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) velocity.x = MoveVelocity;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) velocity.x = -MoveVelocity;

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_UP) == ButtonState::Pressed && !isJumping) {
	velocity.y = -JumpVelocity;
	isJumping = true;
    }

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
	auto bullet = new Bullet(GetGame());
	auto offset = Vector2(32 + 8, (32 + 8) / 2 - 8);
	bullet->SetPosition(GetPosition() + offset);
    }
}

void Player::UpdateActor(float deltaTime) {
    rigidbody->velocity.x = velocity.x * deltaTime;
    rigidbody->velocity.y += velocity.y * deltaTime;

    if (Math::NearZero(rigidbody->velocity.y)) {
	isJumping = false;
    }

    GetGame()->GetRenderer()->GetCamera()->Follow(this);
}
