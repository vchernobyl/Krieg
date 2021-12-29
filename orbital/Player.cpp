#include "Player.h"
#include "Planet.h"
#include "Rocket.h"
#include "Hud.h"
#include "Health.h"
#include "Explosion.h"
#include "Collision.h"
#include <cassert>

Player::Player(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    auto rigidbody = new RigidbodyComponent(this, BodyType::Kinematic);
    auto collider = new CircleColliderComponent(this, 0.5f, GetPosition());
    collider->SetCategoryAndMask(CollisionMask::Player,
				 CollisionMask::Enemy |
				 CollisionMask::EnemyProjectile |
				 CollisionMask::Powerup);

    auto camera = game->GetMainCamera();
    auto scale = camera->GetScale();
    camera->SetScale(scale / 1.5f);

    rocketSound = new AudioComponent(this);

    auto health = new Health(this, 1000);
    health->onDamage = [=]() { hud->SetHealth(health->GetHealth()); };
    health->onDie = [=]() { new Explosion(game, GetPosition()); };

    hud = new Hud(game);
    hud->SetHealth(health->GetHealth());

    SetTag("Player");
}

void Player::ActorInput(const InputState& input) {
    auto actor = GetGame()->GetActorByTag("Planet");
    auto orbit = dynamic_cast<Planet*>(actor);
    assert(orbit);

    auto radius = orbit->GetRadius();
    auto center = orbit->GetCenter();

    auto deltaTime = GetGame()->GetDeltaTime();
    if (input.Keyboard.IsKeyPressed(Key::Left)) {
        angle += speed * deltaTime;
    } else if (input.Keyboard.IsKeyPressed(Key::Right)) {
        angle -= speed * deltaTime;
    }

    if (input.Keyboard.IsKeyPressed(Key::Up)) {
        orbit->SetRadius(radius + orbitSpeed * deltaTime);
    } else if (input.Keyboard.IsKeyPressed(Key::Down)) {
        orbit->SetRadius(radius - orbitSpeed * deltaTime);
    }

    auto x = Math::Cos(angle) * radius + center.x;
    auto y = Math::Sin(angle) * radius + center.y;
    SetPosition(Vector2(x, y));

    auto direction = Vector2::Normalize(orbit->GetPosition() - GetPosition());
    SetRotation(Math::Atan2(direction.y, direction.x));

    if (input.Keyboard.GetKeyState(Key::Space) == ButtonState::Pressed) {
        if (time >= fireRate) {
            time = 0.0f;
            auto rocket = new Rocket(GetGame());
            auto collider = rocket->GetComponent<ColliderComponent>();
	    collider->SetCategoryAndMask(CollisionMask::PlayerProjectile, CollisionMask::Enemy);

	    rocket->SetPosition(GetPosition());
            rocket->SetSpeed(600.0f);
            rocket->Launch(direction);
            rocketSound->PlayEvent("event:/Launch_Rocket");
        }
    }
}

void Player::UpdateActor(float deltaTime) {
    auto position = GetPosition();
    DebugRenderer::DrawLine(position, position + GetForward(), Color::Blue);

    time += deltaTime;
}
