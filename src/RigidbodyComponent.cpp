#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Game.h"
#include "PhysicsWorld.h"

RigidbodyComponent::RigidbodyComponent(Actor* owner, MotionType type) : Component(owner) {
    b2BodyDef bodyDef;
    const Vector2& position = owner->GetPosition();
    bodyDef.position.Set(position.x, position.y);

    if (type == MotionType::PhysicsDriven) bodyDef.type = b2BodyType::b2_dynamicBody;
    if (type == MotionType::GameplayDriven) bodyDef.type = b2BodyType::b2_kinematicBody;
    if (type == MotionType::Fixed) bodyDef.type = b2BodyType::b2_staticBody;

    PhysicsWorld* physicsWorld = owner->GetGame()->GetPhysicsWorld();
    body = physicsWorld->world.CreateBody(&bodyDef);
    physicsWorld->AddRigidbody(this);
}

RigidbodyComponent::~RigidbodyComponent() {
    owner->GetGame()->GetPhysicsWorld()->RemoveRigidbody(this);
}
	
