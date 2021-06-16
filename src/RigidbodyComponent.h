#pragma once

#include "Component.h"
#include "Math.h"

// TODO: All dependencies on Box2D should be hidden away.
#include <b2_body.h>

class RigidbodyComponent : public Component {
public:
    Vector2 velocity;

    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();
private:
    friend class BoxColliderComponent;
    friend class PhysicsWorld;
    
    b2Body* body;
};
