#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"

#include <b2_circle_shape.h>
#include <b2_fixture.h>
#include <b2_body.h>

CircleColliderComponent::CircleColliderComponent(Actor* owner, float radius) : ColliderComponent(owner) {
    b2CircleShape shape;
    shape.m_p.Set(0, 0);
    shape.m_radius = 1;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    RigidbodyComponent* rigidbody = GetAttachedRigidbody();
    if (rigidbody == nullptr) rigidbody = new RigidbodyComponent(owner);
    
    rigidbody->body->CreateFixture(&fixtureDef);
}

