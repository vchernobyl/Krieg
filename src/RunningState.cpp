#include "RunningState.h"
#include "IdleState.h"
#include "Hero.h"

HeroState* RunningState::Update(Hero& hero) {
    if (move->GetVelocity() == 0) {
	return new IdleState();
    }
    if (move->GetVelocity() < 0 && hero.GetDirection() != AnimDirection::Left) {
	hero.SetDirection(AnimDirection::Left);
	anim->ChangeAnim(1, hero.GetDirection());
    }
    if (move->GetVelocity() > 0 && hero.GetDirection() != AnimDirection::Right) {
	hero.SetDirection(AnimDirection::Right);
	anim->ChangeAnim(1, hero.GetDirection());
    }
    return nullptr;
}

void RunningState::Enter(Hero& hero) {
    anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(1, hero.GetDirection());
    move = hero.GetComponent<MoveComponent>();
}
