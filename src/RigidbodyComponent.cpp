#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      force(Vector2::Zero),
      velocity(Vector2::Zero),
      acceleration(Vector2::Zero),
      mass(0), gravity(0) {}

void RigidbodyComponent::Update(float deltaTime) {
    acceleration.x = force.x / mass;
    acceleration.y = gravity + force.y / mass;
    velocity += acceleration * deltaTime;
    Vector2 position = owner->GetPosition() + velocity * deltaTime;
    owner->SetPosition(position);
}
