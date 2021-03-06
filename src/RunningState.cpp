#include "RunningState.h"
#include "IdleState.h"
#include "AnimSpriteComponent.h"
#include "Hero.h"

HeroState* RunningState::ProcessInput(Hero& hero, const InputState& input) {
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Released) {
	return new IdleState();
    }
    return nullptr;
}

void RunningState::Enter(Hero& hero) {
    auto anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(1);
}
