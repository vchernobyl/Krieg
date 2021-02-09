#include "Component.h"

Component::Component(Actor* owner, int updateOrder)
    : owner(owner),
      updateOrder(updateOrder) {
    this->owner->AddComponent(this);
}

Component::~Component() {
    owner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {}
