#pragma once

#include "Component.h"
#include "Math.h"

struct RigidbodyComponent : public Component {
    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();
    void Update(float deltaTime) override;

    Vector2 velocity;
};
