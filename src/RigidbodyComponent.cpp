#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Game.h"
#include "PhysicsWorld.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner)
    : Component(owner),
      bodyType(BodyType::Dynamic) {
    owner->GetGame()->GetPhysicsWorld()->AddRigidbody(this);
}

RigidbodyComponent::~RigidbodyComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveRigidbody(this);
}

void RigidbodyComponent::Update(float deltaTime) {
    owner->Translate(velocity);
}
