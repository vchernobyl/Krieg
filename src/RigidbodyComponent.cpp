#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Game.h"
#include "PhysicsWorld.h"

#include <b2_world.h>
#include <b2_body.h>
#include <b2_math.h>

RigidbodyComponent::RigidbodyComponent(Actor* owner, MotionType type) : Component(owner) {
    b2BodyDef bodyDef;
    const Vector2& position = owner->GetPosition();
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = true;

    if (type == MotionType::Dynamic) bodyDef.type = b2BodyType::b2_dynamicBody;
    if (type == MotionType::Kinematic) bodyDef.type = b2BodyType::b2_kinematicBody;
    if (type == MotionType::Static) bodyDef.type = b2BodyType::b2_staticBody;

    PhysicsWorld* physicsWorld = owner->GetGame()->GetPhysicsWorld();
    body = physicsWorld->world->CreateBody(&bodyDef);
    physicsWorld->AddRigidbody(this);
}

RigidbodyComponent::~RigidbodyComponent() {
    PhysicsWorld* world = owner->GetGame()->GetPhysicsWorld();
    world->RemoveRigidbody(this);
}
	

void RigidbodyComponent::SetVelocity(const Vector2& velocity) {
    body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

Vector2 RigidbodyComponent::GetVelocity() const {
    b2Vec2 vel = body->GetLinearVelocity();
    return Vector2(vel.x, vel.y);
}

void RigidbodyComponent::ApplyForce(const Vector2& force) {
    bool awake = true;

    if (Math::NearZero(force.Length())) {
	awake = false;
    }

    body->ApplyForceToCenter(b2Vec2(force.x, force.y), awake);
}

void RigidbodyComponent::ApplyImpulse(const Vector2& impulse) {
    bool awake = true;

    if (Math::NearZero(impulse.Length())) {
	awake = false;
    }

    body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), awake);
}

float RigidbodyComponent::GetMass() const {
    return body->GetMass();
}

void RigidbodyComponent::SetGravityScale(float scale) {
    body->SetGravityScale(scale);
}
