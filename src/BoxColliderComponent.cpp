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
    auto thisBox = GetBox();

    auto topLeft = thisBox.position - (otherBox.position + otherBox.size);
    auto fullSize = thisBox.size + otherBox.size;
    auto minkowski = Rectangle(topLeft, fullSize);

    Debug::DrawRect(thisBox);
    Debug::DrawRect(otherBox);

    SDL_Log("x=%f, y=%f, w=%f, h=%f", topLeft.x, topLeft.y, fullSize.x, fullSize.y);
    if (minkowski.Contains(Vector2::Zero)) {
	SDL_Log("collision!");
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    return;
}

Rectangle& BoxColliderComponent::GetBox() {
    // TODO: Update the box position inside the Update function.
    box.position = owner->GetPosition() + offset;
    box.size = size;
    return box;
}

