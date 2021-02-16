#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      angularSpeed(0.0f),
      forwardSpeed(0.0f) {}


void MoveComponent::Update(float deltaTime) {
    if (!Math::NearZero(angularSpeed)) {
	float rotation = owner->GetRotation();
	rotation += angularSpeed * deltaTime;
	owner->SetRotation(rotation);
    }
    if (!Math::NearZero(forwardSpeed)) {
	Vector2 position = owner->GetPosition();
	position += owner->GetForward() * forwardSpeed * deltaTime;
	owner->SetPosition(position);
    }
}
