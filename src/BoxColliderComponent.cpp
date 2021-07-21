#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"

#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_body.h>
#include <b2_math.h>
#include <b2_types.h>

CollisionCategory operator|(CollisionCategory lhs, CollisionCategory rhs) {
    return static_cast<CollisionCategory>(
	static_cast<uint16>(lhs) |
	static_cast<uint16>(rhs));
}

BoxColliderComponent::BoxColliderComponent(Actor* owner, const Vector2& size) : ColliderComponent(owner) {
    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;

    b2Vec2 center(halfWidth, halfHeight);
    b2PolygonShape shape;

    shape.SetAsBox(halfWidth, halfHeight, center, 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    // TODO: I don't have better idea yet, but I think this will have to be refactored later on.
    RigidbodyComponent* rigidbody = GetAttachedRigidbody();
    if (rigidbody == nullptr) rigidbody = new RigidbodyComponent(owner);
    
    rigidbody->body->CreateFixture(&fixtureDef);
}

void BoxColliderComponent::SetCollisionFilter(const CollisionFilter& filter) {
    RigidbodyComponent* rigidbody = GetAttachedRigidbody();
    b2Fixture* fixture = rigidbody->body->GetFixtureList();
    b2Filter b2Filter = fixture->GetFilterData();
    b2Filter.maskBits = static_cast<uint16>(filter.mask);
    b2Filter.categoryBits = static_cast<uint16>(filter.category);
    fixture->SetFilterData(b2Filter);
}
