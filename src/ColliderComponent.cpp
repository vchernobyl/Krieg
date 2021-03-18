#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Actor* owner)
    : Component(owner), layer(CollisionLayer::Default) {
    owner->GetGame()->GetPhysicsWorld()->AddCollider(this);
}

ColliderComponent::~ColliderComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveCollider(this);
}
