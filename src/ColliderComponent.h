#pragma once

#include "Component.h"
#include "Math.h"

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    class RigidbodyComponent* GetAttachedRigidbody() const;
};
