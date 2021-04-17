#include "Hero.h"
#include "Game.h"
#include "Renderer.h"
#include "Camera.h"
#include "IdleState.h"
#include "Math.h"
#include <vector>
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

Hero::Hero(Game* game) : Actor(game), state(new IdleState), direction(AnimDirection::Right) {
    animation = new AnimSpriteComponent(this, 200);
    std::vector<AnimFrameData> animFrameData = {
	{ 0, 3, true },
	{ 3, 6, true },
	{ 9, 5, false },
	{ 14, 4, false },
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

    move = new MoveComponent(this);
    move->SetMaxSpeed(200.0f);

    jump = new JumpComponent(this);
    jump->SetInitialPosition(GetPosition().y);
    jump->SetMaxHeight(75.0f);
    jump->SetTimeToPeak(0.5f);

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(50 * GetScale(), 37 * GetScale()));
    new RigidbodyComponent(this);

    SetPosition(Vector2(1100, 600));

    state->Enter(*this);
}

void Hero::ActorInput(const InputState& inputState) {
    HeroState* newState = state->ProcessInput(*this, inputState);
    if (newState) {
	delete state;
	state = newState;
	state->Enter(*this);
    }
}

void Hero::UpdateActor(float deltaTime) {
    HeroState* newState = state->Update(*this);
    if (newState) {
	delete state;
	state = newState;
	state->Enter(*this);
    }

    Camera* cam = GetGame()->GetRenderer()->GetCamera();
    cam->Follow(this);
}
