#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Game.h"
#include "PhysicsWorld.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner) : Component(owner) {
    b2BodyDef bodyDef;
    const Vector2& position = owner->GetPosition();
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);

    PhysicsWorld* physicsWorld = owner->GetGame()->GetPhysicsWorld();
    body = physicsWorld->world.CreateBody(&bodyDef);
    physicsWorld->AddRigidbody(this);
}

RigidbodyComponent::~RigidbodyComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveRigidbody(this);
}
