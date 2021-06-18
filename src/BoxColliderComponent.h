#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collision.h"
#include "Math.h"

// TODO: This guy has to be hidden away.
#include <b2_polygon_shape.h>
#include <b2_body.h>
#include <box2d.h>

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();
    void SetBox(float width, float height);
    const Vector2& GetSize();
private:
    b2PolygonShape box;
    Vector2 size;
};

inline void BoxColliderComponent::SetBox(float width, float height) {
    box.SetAsBox(width * 0.5f, height * 0.5f);
    size = Vector2(width * 0.5f, height * 0.5f);
    // TODO: Can crash if rigidbody not set, needs a better mechanism to create a fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    GetAttachedRigidbody()->body->CreateFixture(&fixtureDef);
}

inline const Vector2& BoxColliderComponent::GetSize() {
    return size;
}
