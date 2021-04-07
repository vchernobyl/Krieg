#pragma once

#include "Component.h"
#include "Math.h"

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();
    void Update(float deltaTime) override;
private:
    Vector2 velocity;
};
