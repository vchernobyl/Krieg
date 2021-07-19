#include "BoxColliderComponent.h"
#include "Actor.h"

#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_body.h>
#include <b2_math.h>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

void BoxColliderComponent::SetSize(float width, float height) {
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    b2Vec2 center(hw, hh);
    b2PolygonShape box;

    box.SetAsBox(hw, hh, center, 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    // TODO: I don't have better idea yet, but I think this will have to be refactored later on.
    RigidbodyComponent* rb = GetAttachedRigidbody();
    if (rb == nullptr) rb = new RigidbodyComponent(owner);
    
    rb->body->CreateFixture(&fixtureDef);
}
