#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner) :
    Component(owner),
    radius(0) {}

const Vector2& CircleComponent::GetCenter() const {
    return owner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b) {
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;
    return distSq <= radiiSq;
}
