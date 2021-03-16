#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner) {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other) {
    CollisionInfo info;
    return info;
}

void BoxColliderComponent::ResolveOverlap(const CollisionInfo& info) {
    return;
}
