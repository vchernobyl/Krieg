#include "JumpingState.h"
#include "IdleState.h"
#include "Hero.h"

HeroState* JumpingState::ProcessInput(Hero& hero, const InputState& input) {
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Left);
	anim->SetDirection(hero.GetDirection());
    }
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Right);
	anim->SetDirection(hero.GetDirection());
    }
    return nullptr;
}

HeroState* JumpingState::Update(Hero& hero) {
    if (jump->IsOnGround()) {
	return new IdleState();
    }
    return nullptr;
}

void JumpingState::Enter(Hero& hero) {
    anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(3, hero.GetDirection());
    jump = hero.GetComponent<JumpComponent>();
    move = hero.GetComponent<MoveComponent>();
}
