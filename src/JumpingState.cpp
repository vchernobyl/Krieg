#include "JumpingState.h"
#include "IdleState.h"
#include "Hero.h"

HeroState* JumpingState::Update(Hero& hero) {
    if (jump->IsOnGround()) {
	return new IdleState();
    }
    if (move->GetVelocity() > 0 && hero.GetDirection() != AnimDirection::Right) {
	anim->SetDirection(AnimDirection::Right);
    }
    if (move->GetVelocity() < 0 && hero.GetDirection() != AnimDirection::Left) {
	anim->SetDirection(AnimDirection::Left);
    }
    return nullptr;
}

void JumpingState::Enter(Hero& hero) {
    anim = hero.GetComponent<AnimSpriteComponent>();
    anim->ChangeAnim(3, hero.GetDirection());
    jump = hero.GetComponent<JumpComponent>();
    move = hero.GetComponent<MoveComponent>();
}
