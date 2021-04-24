#pragma once

#include "Component.h"
#include "Math.h"

enum class BodyType {
    Dynamic,
    Kinematic
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();
    void Update(float deltaTime) override;

    bool IsDynamic() const { return bodyType == BodyType::Dynamic; }

    Vector2 velocity;
    BodyType bodyType;
};
