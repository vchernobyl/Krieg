#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      mass(1.0f), gravity(0) {}

void RigidbodyComponent::Update(float deltaTime) {
    acceleration.x = force.x / mass;
    acceleration.y = force.y / mass;
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
    owner->SetPosition(owner->GetPosition() + position);
}
