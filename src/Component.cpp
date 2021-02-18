#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
    : owner(owner),
      updateOrder(updateOrder) {
    owner->AddComponent(this);
}

Component::~Component() {
    owner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {}

void Component::ProcessInput(const uint8_t* keyState) {}
