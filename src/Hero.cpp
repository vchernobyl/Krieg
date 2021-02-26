#include "Hero.h"
#include "Game.h"
#include "Math.h"
#include <vector>

Hero::Hero(Game* game) : Actor(game), animState(Idle) {
    animation = new AnimSpriteComponent(this);
    std::vector<AnimFrameData> animFrameData = {
	{ 0, 3 },
	{ 3, 6 },
	{ 9, 5 },
	{ 14, 4 },
    };
    std::vector<SDL_Texture*> images = {
	game->GetTexture("assets/adventurer-idle-00.png"),
	game->GetTexture("assets/adventurer-idle-01.png"),
	game->GetTexture("assets/adventurer-idle-02.png"),
	game->GetTexture("assets/adventurer-run-00.png"),
	game->GetTexture("assets/adventurer-run-01.png"),
	game->GetTexture("assets/adventurer-run-02.png"),
	game->GetTexture("assets/adventurer-run-03.png"),
	game->GetTexture("assets/adventurer-run-04.png"),
	game->GetTexture("assets/adventurer-run-05.png"),
	game->GetTexture("assets/adventurer-attack1-00.png"),
	game->GetTexture("assets/adventurer-attack1-01.png"),
	game->GetTexture("assets/adventurer-attack1-02.png"),
	game->GetTexture("assets/adventurer-attack1-03.png"),
	game->GetTexture("assets/adventurer-attack1-04.png"),
	game->GetTexture("assets/adventurer-jump-00.png"),
	game->GetTexture("assets/adventurer-jump-01.png"),
	game->GetTexture("assets/adventurer-jump-02.png"),
	game->GetTexture("assets/adventurer-jump-03.png"),
    };
    AnimData animData = { images, animFrameData };
    animation->SetAnimData(animData);
    animation->SetAnimFPS(10.0f);
    animation->ChangeAnim(Idle);

    movement = new MovementComponent(this);
    movement->SetSpeed(200.0f);

    rigidbody = new RigidbodyComponent(this);
    rigidbody->SetGravity(10.0f);

    SetScale(1.5f);
}

void Hero::UpdateActor(float deltaTime) {
    float x = GetPosition().x;
    float y = GetPosition().y > 150.0f ? 150.0f : GetPosition().y;
    SetPosition(Vector2(x, y));
}

void Hero::ActorInput(const InputState& inputState) {
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed) {
	animState = Jump;
	animation->ChangeAnim(animState);
	rigidbody->AddForce(Vector2::NegUnitY * 2000.0f);
    }
    switch (animState) {
    case Idle:
	if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Pressed) {
	    animState = Run;
	    animation->ChangeAnim(animState, SDL_FLIP_HORIZONTAL);
	} else if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Pressed) {
	    animState = Run;
	    animation->ChangeAnim(animState);
	}
	break;
    case Run:
	if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Released) {
	    animState = Idle;
	    animation->ChangeAnim(animState, SDL_FLIP_HORIZONTAL);
	} else if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Released) {
	    animState = Idle;
	    animation->ChangeAnim(animState);
	}
	break;
    case Attack:
	break;
    }
}
