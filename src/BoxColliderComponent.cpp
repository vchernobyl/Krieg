#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"

#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_body.h>
#include <b2_math.h>

BoxColliderComponent::BoxColliderComponent(Actor* owner, const Vector2& size) : ColliderComponent(owner) {
    b2PolygonShape shape;

    const Vector2& position = owner->GetPosition();
    Vector2 center = Vector2(position.x - size.x / 2.0f, position.y - size.y / 2.0f);
    shape.SetAsBox(size.x / 2.0f, size.y / 2.0f, b2Vec2(center.x, center.y), 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    RigidbodyComponent* rigidbody = GetAttachedRigidbody();
    if (rigidbody == nullptr) rigidbody = new RigidbodyComponent(owner);
    
    fixture = rigidbody->body->CreateFixture(&fixtureDef);
}
