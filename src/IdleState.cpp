#include "IdleState.h"
#include "RunningState.h"
#include "AnimSpriteComponent.h"
#include "Hero.h"

HeroState* IdleState::ProcessInput(Hero& hero, const InputState& input) {
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Left);
	return new RunningState();
    }
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Right);
	return new RunningState();
    }
    return nullptr;
}

void IdleState::Enter(Hero& hero) {
    auto anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(0, hero.GetDirection());
}
