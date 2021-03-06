#include "RunningState.h"
#include "IdleState.h"
#include "Hero.h"

HeroState* RunningState::ProcessInput(Hero& hero, const InputState& input) {
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Released) {
	return new IdleState();
    }
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Released) {
	return new IdleState();
    }
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Left);
	anim->ChangeAnim(1, hero.GetDirection());
    }
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed) {
	hero.SetDirection(AnimDirection::Right);
	anim->ChangeAnim(1, hero.GetDirection());
    }
    return nullptr;
}

void RunningState::Update(Hero& hero) {
}

void RunningState::Enter(Hero& hero) {
    anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(1, hero.GetDirection());
    move = hero.GetComponent<MoveComponent>();
}
