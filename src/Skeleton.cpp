#include "Skeleton.h"
#include "Game.h"
#include "RigidbodyComponent.h"
#include "Math.h"
#include <vector>

Skeleton::Skeleton(Game* game) : Actor(game), animState(Idle) {
    animation = new AnimSpriteComponent(this);
    std::vector<AnimFrameData> animFrameData = {
	{ 0, 3 },
	{ 3, 6 },
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
    };
    AnimData animData = { images, animFrameData };
    animation->SetAnimData(animData);
    animation->SetAnimFPS(10.0f);
    animation->ChangeAnim(Run);

    rigidbody = new RigidbodyComponent(this);
    rigidbody->SetMass(1.0f);
    SetScale(2.0f);
}

void Skeleton::ActorInput(const uint8_t* keyState) {
    if (keyState[SDL_SCANCODE_RIGHT]) {
	rigidbody->AddForce(Vector2::UnitX * 20000.0f);
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
	rigidbody->AddForce(Vector2::NegUnitX * 20000.0f);
    }
}

void Skeleton::UpdateActor(float deltaTime) {
    rigidbody->ResetForce();
}
