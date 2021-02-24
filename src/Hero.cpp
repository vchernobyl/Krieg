#include "Hero.h"
#include "Game.h"
#include "Math.h"
#include <vector>

Hero::Hero(Game* game) : Actor(game), animState(Idle) {
    animation = new AnimSpriteComponent(this);
    std::vector<AnimFrameData> animFrameData = {
	{ 0, 3 },
	{ 3, 6 },
	{10, 4 },
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
    };
    AnimData animData = { images, animFrameData };
    animation->SetAnimData(animData);
    animation->SetAnimFPS(10.0f);
    animation->ChangeAnim(Run, SDL_FLIP_HORIZONTAL);

    input = new MovementComponent(this);
    input->SetSpeed(200.0f);

    SetScale(1.5f);
}

void Hero::ActorInput(const uint8_t* keyState) {
    // SDL_RendererFlip direction = SDL_FLIP_NONE;
    // if (keyState[SDL_SCANCODE_LEFT]) {
    // 	direction = SDL_FLIP_HORIZONTAL;
    // 	animation->ChangeAnim(Run, direction);
    // } else if (keyState[SDL_SCANCODE_RIGHT]) {
    // 	animation->ChangeAnim(Run, direction);
    // } else {
    // 	animation->ChangeAnim(Idle, direction);
    // }
}
