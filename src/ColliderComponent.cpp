#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Actor* owner)
    : Component(owner), layer(CollisionLayer::Default) {}
