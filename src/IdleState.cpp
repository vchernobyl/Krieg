#include "IdleState.h"
#include "AnimSpriteComponent.h"
#include "RigidbodyComponent.h"
#include "Hero.h"

void IdleState::ProcessInput(Hero& hero, const InputState& input) {
    return;
}

void IdleState::Enter(Hero& hero) {
    AnimSpriteComponent* anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(1);

    RigidbodyComponent* spr = hero.GetComponent<RigidbodyComponent>();
    if (spr == nullptr) {
	SDL_Log("component not attached");
    } else {
	SDL_Log("component found");
    }
}
