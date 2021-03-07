#include "JumpingState.h"
#include "IdleState.h"
#include "Hero.h"

HeroState* JumpingState::ProcessInput(Hero& hero, const InputState& input) {
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT) && hero.GetDirection() != AnimDirection::Left) {
	hero.SetDirection(AnimDirection::Left);
	anim->SetDirection(hero.GetDirection());
    }
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) && hero.GetDirection() != AnimDirection::Right) {
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
