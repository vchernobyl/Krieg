#include "RigidbodyComponent.h"
#include "Actor.h"
#include "PhysicsWorld.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner) : Component(owner) {
    owner->GetGame()->GetPhysicsWorld()->AddRigidbody(this);
}

RigidbodyComponent::~RigidbodyComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveRigidbody(this);
}
