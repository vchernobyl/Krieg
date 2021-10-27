#include "PhysicsWorld.h"
#include "Box2DDebugRenderer.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Math.h"

#include <algorithm>
#include <cassert>
#include <SDL/SDL.h>

#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_world_callbacks.h>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(class b2Contact* contact) {
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
};

class QueryCallback : public b2QueryCallback {
public:
    b2Fixture* target;
    
    bool ReportFixture(b2Fixture* fixture) {
	SDL_Log("query hit");
	target = fixture;
	return false;
    }

    // TODO: This needs to be improved, very hacky at the moment.
    Actor* GetActor() {
	if (target) {
	    uintptr_t data = target->GetBody()->GetUserData().pointer;
	    target = nullptr;
	    return reinterpret_cast<Actor*>(data);
	}
	return nullptr;
    }
};

const int32 VelocityIterations = 8;
const int32 PositionIterations = 3;

PhysicsWorld::PhysicsWorld(const Vector2& gravity)
    : world(new b2World(b2Vec2(gravity.x, gravity.y))),
      debugRenderer(new Box2DDebugRenderer),
      contactListener(new ContactListener),
      queryCallback(new QueryCallback) {
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

Actor* PhysicsWorld::CheckOverlap(const Vector2& point) {
    b2Vec2 lowerBounds(point.x, point.y);
    b2Vec2 upperBounds(point.x, point.y);
    const b2AABB aabb = { lowerBounds, upperBounds };
    world->QueryAABB(queryCallback, aabb);
    return queryCallback->GetActor();
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
