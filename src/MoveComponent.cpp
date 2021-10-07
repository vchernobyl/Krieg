#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      angularSpeed(0.0f),
      forwardSpeed(0.0f) {
}

void MoveComponent::Update(float deltaTime) {
    if (!Math::NearZero(angularSpeed)) {
	float rot = owner->GetRotation();
	rot += angularSpeed * deltaTime;
	owner->SetRotation(rot);
    }

    if (!Math::NearZero(forwardSpeed)) {
	Vector2 pos = owner->GetPosition();
	pos += owner->GetForward() * forwardSpeed * deltaTime;

	if (pos.x < -512.0f) {
	    pos.x = 510.0f;
	} else if (pos.x > 512.0f) {
	    pos.x = -510.0f;
	} else if (pos.y > 384.0f) {
	    pos.y = -382.0f;
	} else if (pos.y < -384.0) {
	    pos.y = 382.0f;
	}

	owner->SetPosition(pos);
    }
}
