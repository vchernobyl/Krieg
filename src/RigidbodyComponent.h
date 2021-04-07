#pragma once

#include "Component.h"
#include "Math.h"

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();
private:
    Vector2 velocity;
};
