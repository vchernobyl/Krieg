#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collision.h"
#include "Math.h"

// TODO: This guy has to be hidden away.
#include <b2_polygon_shape.h>
#include <b2_body.h>

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();
    void SetBox(float width, float height);
private:
    b2PolygonShape box;
};

inline void BoxColliderComponent::SetBox(float width, float height) {
    box.SetAsBox(width * 0.5f, height * 0.5f);
    GetAttachedRigidbody()->body->CreateFixture(&box, 0.0f);
}
