#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Debug.h"

#include <algorithm>
#include <cmath>
#include <cassert>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other) {
    CollisionInfo info;

    auto otherBox = dynamic_cast<BoxColliderComponent*>(other)->GetBox();
    auto box = GetBox();

    auto topLeft = box.position - (otherBox.position + otherBox.size);
    auto fullSize = box.size + otherBox.size;
    auto minkowski = Rectangle(topLeft, fullSize);

    Debug::DrawRect(box);
    Debug::DrawRect(otherBox);
    
    if (minkowski.Contains(Vector2::Zero)) {
	SDL_Log("collision!");
    } else {
	SDL_Log("no collision!");
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    
//    float minDist = Math::Fabs(Vecto2::Zero.x - 
    return;
}

void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
