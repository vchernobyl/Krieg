#include "RigidbodyComponent.h"
#include "PhysicsWorld.h"
#include "Actor.h"
#include "Game.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>

RigidbodyComponent::RigidbodyComponent(Actor* owner, BodyType type) : Component(owner) {
    b2BodyDef bodyDef;
    const Vector2& position = owner->GetPosition();
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(owner);

    if (type == BodyType::Dynamic) bodyDef.type = b2BodyType::b2_dynamicBody;
    if (type == BodyType::Kinematic) bodyDef.type = b2BodyType::b2_kinematicBody;
    if (type == BodyType::Static) bodyDef.type = b2BodyType::b2_staticBody;

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

Vector2 RigidbodyComponent::GetPosition() const {
    b2Vec2 pos = body->GetPosition();
    return Vector2(pos.x, pos.y);
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

void RigidbodyComponent::SetBullet(bool flag) {
    body->SetBullet(flag);
}

void RigidbodyComponent::SetPosition(const Vector2& position) {
    body->SetTransform(b2Vec2(position.x, position.y), body->GetAngle());
}

