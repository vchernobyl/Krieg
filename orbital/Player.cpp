#include "Player.h"
#include "Planet.h"
#include "Rocket.h"
#include "HUD.h"
#include "DamageReceiver.h"
#include "Explosion.h"

#include <SDL/SDL.h> // TODO: I've done fucked up here real bad.
#include <cassert>

Player::Player(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    auto rigidbody = new RigidbodyComponent(this, BodyType::Kinematic);
    auto collider = new CircleColliderComponent(this, 0.5f, GetPosition());
    collider->SetCollisionFilter(CollisionCategory::Player);

    auto camera = game->GetMainCamera();
    auto scale = camera->GetScale();
    camera->SetScale(scale / 1.5f);

    rocketSound = new AudioComponent(this);

    auto damageReceiver = new DamageReceiver(this, 50);
    damageReceiver->SetOnReceiveDamage([=]() {
        hud->SetHealth(damageReceiver->GetHealth());
    });
    damageReceiver->SetOnZeroHealth([=]() {
        new Explosion(game, GetPosition());
    });

    hud = new HUD(game);
    hud->SetHealth(50);

    SetTag("Player");
}

void Player::ActorInput(const InputState& input) {
    auto actor = GetGame()->GetActorByTag("Planet");
    auto orbit = dynamic_cast<Planet*>(actor);
    assert(orbit);

    auto radius = orbit->GetRadius();
    auto center = orbit->GetCenter();

    auto deltaTime = GetGame()->GetDeltaTime();
    if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_LEFT)) {
        angle += speed * deltaTime;
    } else if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
        angle -= speed * deltaTime;
    }

    if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_UP)) {
        orbit->SetRadius(radius + orbitSpeed * deltaTime);
    } else if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_DOWN)) {
        orbit->SetRadius(radius - orbitSpeed * deltaTime);
    }

    auto x = Math::Cos(angle) * radius + center.x;
    auto y = Math::Sin(angle) * radius + center.y;
    SetPosition(Vector2(x, y));

    auto direction = Vector2::Normalize(orbit->GetPosition() - GetPosition());
    SetRotation(Math::Atan2(direction.y, direction.x));

    if (input.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
        auto rocket = new Rocket(GetGame());
        rocket->SetCollisionFilter(CollisionCategory::Player, CollisionCategory::Enemy);
        rocket->SetPosition(GetPosition());
        rocket->SetSpeed(600.0f);
        rocket->Launch(direction);
        rocketSound->PlayEvent("event:/Launch_Rocket");
    }
}

void Player::UpdateActor(float deltaTime) {
    auto position = GetPosition();
    DebugRenderer::DrawLine(position, position + GetForward(), Color::Blue);
}
