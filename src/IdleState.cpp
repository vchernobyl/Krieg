#include "IdleState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "AnimSpriteComponent.h"
#include "Hero.h"

HeroState* IdleState::Update(Hero& hero) {
    if (move->GetVelocity() > 0) {
	hero.SetDirection(AnimDirection::Right);
	return new RunningState();
    }
    if (move->GetVelocity() < 0) {
	hero.SetDirection(AnimDirection::Left);
	return new RunningState();
    }
    if (jump->IsJumping()) {
	return new JumpingState();
    }
    return nullptr;
}

void IdleState::Enter(Hero& hero) {
    auto anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(0, hero.GetDirection());
    move = hero.GetComponent<MoveComponent>();
    jump = hero.GetComponent<JumpComponent>();
}
