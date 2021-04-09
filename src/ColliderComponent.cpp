#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PhysicsWorld.h"
#include "Actor.h"

ColliderComponent::ColliderComponent(Actor* owner)
    : Component(owner), layer(CollisionLayer::Default) {
    owner->GetGame()->GetPhysicsWorld()->AddCollider(this);
}

ColliderComponent::~ColliderComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveCollider(this);
}

RigidbodyComponent* ColliderComponent::GetAttachedRigidbody() const {
    return owner->GetComponent<RigidbodyComponent>();
}
