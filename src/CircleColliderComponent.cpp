#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_body.h>

CircleColliderComponent::CircleColliderComponent(Actor* owner, float radius, const Vector2& center)
    : ColliderComponent(owner) {
    b2CircleShape shape;
    shape.m_p.Set(center.x, center.y);
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;

    RigidbodyComponent* rigidbody = GetAttachedRigidbody();
    if (rigidbody == nullptr) rigidbody = new RigidbodyComponent(owner);
    
    fixture = rigidbody->body->CreateFixture(&fixtureDef);
}


