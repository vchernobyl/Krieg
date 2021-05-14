#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

Component::Component(Actor* owner, int updateOrder)
    : owner(owner),
      updateOrder(updateOrder) {
    owner->AddComponent(this);
}

Component::~Component() {
    owner->RemoveComponent(this);
}
