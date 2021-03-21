#include "ColliderComponent.h"
#include "SDL.h"

ColliderComponent::ColliderComponent(Actor* owner)
    : Component(owner), layer(CollisionLayer::Default) {
    SDL_Log("collider constructor");
    owner->GetGame()->GetPhysicsWorld()->AddCollider(this);
}

ColliderComponent::~ColliderComponent() {
    SDL_Log("collider destructor");
    owner->GetGame()->GetPhysicsWorld()->RemoveCollider(this);
}
