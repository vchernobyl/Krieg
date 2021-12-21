#include "Player.h"
#include "Orbit.h"
#include <SDL/SDL.h> // TODO: I've done fucked up here real bad.
#include <cassert>

Player::Player(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    auto camera = game->GetMainCamera();
    auto scale = camera->GetScale();
    camera->SetScale(scale / 1.5f);
}

void Player::ActorInput(const InputState& input) {
    auto actor = GetGame()->GetActorByTag("Orbit");
    auto orbit = dynamic_cast<Orbit*>(actor);
    assert(orbit);

    auto radius = orbit->GetRadius();
    auto center = orbit->GetCenter();

    if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_LEFT)) {
        angle += 5.0f * GetGame()->GetDeltaTime();
    }
    else if (input.Keyboard.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
        angle -= 5.0f * GetGame()->GetDeltaTime();
    }

    auto x = Math::Cos(angle) * radius + center.x;
    auto y = Math::Sin(angle) * radius + center.y;

    SetPosition(Vector2(x, y));
}

void Player::UpdateActor(float deltaTime) {
}

