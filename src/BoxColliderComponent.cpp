#include "BoxColliderComponent.h"
#include "Actor.h"

#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_body.h>
#include <b2_math.h>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

void BoxColliderComponent::SetBox(float width, float height) {
    float hw = width * 0.5f;
    float hh = height * 0.5f;

    b2Vec2 center(hw, hh);
    b2PolygonShape box;

    box.SetAsBox(hw, hh, center, 0.0f);

    // TODO: Can crash if rigidbody not set, needs a better mechanism to create a fixture.
    // Maybe attach rigidbody automatically whenever a collider is attached?
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    GetAttachedRigidbody()->body->CreateFixture(&fixtureDef);
}
