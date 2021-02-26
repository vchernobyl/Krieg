#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      mass(1.0f), gravity(0) {}

void RigidbodyComponent::Update(float deltaTime) {
    // BUG: After calculating acceleration, velocity and position we set the force to zero vector.
    // However, velocity AND position will get incremented in every frame even though no force is applied
    // and the object is not moving.
    acceleration.x = force.x / mass;
    acceleration.y = (force.y + gravity) / mass;
    velocity += acceleration * deltaTime; // velocity + acceleration * dt is CHANGE in velocity
    position += velocity * deltaTime;     // position + velocity     * dt is CHANGE in position
    SDL_Log("f.y = %f, acc = %f, vel = %f, pos = %f", force.y, acceleration.y, velocity.y, position.y);
    owner->SetPosition(owner->GetPosition() + position);
    force = Vector2::Zero;
}
