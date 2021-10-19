#include "PhysicsWorld.h"
#include "Box2DDebugRenderer.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Math.h"

#include <algorithm>
#include <cassert>

#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_world_callbacks.h>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(class b2Contact* contact);
};

void ContactListener::BeginContact(b2Contact* contact) {
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    Contact contactInfo;
    b2Vec2 contactNormal = worldManifold.normal;
    b2Vec2 contactPoint = worldManifold.points[0];

    contactInfo.normal = Vector2(contactNormal.x, contactNormal.y);
    contactInfo.point = Vector2(contactPoint.x, contactPoint.y);

    uintptr_t pointerA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Actor* ownerA = reinterpret_cast<Actor*>(pointerA);

    uintptr_t pointerB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    Actor* ownerB = reinterpret_cast<Actor*>(pointerB);

    contactInfo.other = ownerB;
    ownerA->OnBeginContact(contactInfo);

    contactInfo.other = ownerA;
    ownerB->OnBeginContact(contactInfo);
}

const int32 VelocityIterations = 8;
const int32 PositionIterations = 3;

PhysicsWorld::PhysicsWorld(const Vector2& gravity)
    : world(new b2World(b2Vec2(gravity.x, gravity.y))),
      debugRenderer(new Box2DDebugRenderer()),
      contactListener(new ContactListener()) {
    world->SetDebugDraw(debugRenderer);
    world->SetContactListener(contactListener);
}

void PhysicsWorld::Shutdown() {
    delete debugRenderer;
    delete world;
    delete contactListener;
}

void PhysicsWorld::Step(float timeStep) {
    world->Step(timeStep, VelocityIterations, PositionIterations);

    for (const auto rb : rigidbodies) {
	auto owner = rb->GetOwner();
	owner->SetPosition(rb->GetPosition());
    }

    world->DebugDraw();
}

void PhysicsWorld::AddCollider(ColliderComponent* collider) {
    colliders.push_back(collider);
}

void PhysicsWorld::RemoveCollider(ColliderComponent* collider) {
    auto iter = std::find(colliders.begin(), colliders.end(), collider);
    if (iter != colliders.end()) {
	std::iter_swap(iter, colliders.end() - 1);
	colliders.pop_back();
    }
}

void PhysicsWorld::AddRigidbody(RigidbodyComponent* rigidbody) {
    rigidbodies.push_back(rigidbody);
}

void PhysicsWorld::RemoveRigidbody(RigidbodyComponent* rigidbody) {
    auto iter = std::find(rigidbodies.begin(), rigidbodies.end(), rigidbody);
    if (iter != rigidbodies.end()) {
	world->DestroyBody(rigidbody->body);
	std::iter_swap(iter, rigidbodies.end() - 1);
	rigidbodies.pop_back();
    }
}
