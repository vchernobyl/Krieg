#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PhysicsWorld.h"
#include "Game.h"
#include "Actor.h"

#include <box2d/b2_fixture.h>
#include <box2d/b2_types.h>
#include <cassert>

CollisionCategory operator|(CollisionCategory lhs, CollisionCategory rhs) {
    return static_cast<CollisionCategory>(
        static_cast<uint16>(lhs) |
        static_cast<uint16>(rhs));
}

ColliderComponent::ColliderComponent(Actor* owner) : Component(owner), fixture(nullptr) {
    owner->GetGame()->GetPhysicsWorld()->AddCollider(this);
}

ColliderComponent::~ColliderComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveCollider(this);
}

RigidbodyComponent* ColliderComponent::GetAttachedRigidbody() const {
    return owner->GetComponent<RigidbodyComponent>();
}

// TODO: Split this function up into two.
// Also remove CollisionCategory and pass regular uin16 instead.
void ColliderComponent::SetCollisionFilter(CollisionCategory category, CollisionCategory mask) {
    assert(fixture);
    
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = static_cast<uint16>(category);
    filter.maskBits = static_cast<uint16>(mask);
    fixture->SetFilterData(filter);
}

void ColliderComponent::SetSensor(bool flag) {
    assert(fixture);
    fixture->SetSensor(flag);
}

bool ColliderComponent::IsSensor() const {
    assert(fixture);
    return fixture->IsSensor();
}
