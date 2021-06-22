#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"
#include "Actor.h"
#include "Math.h"
#include "DebugRenderer.h"
#include "Box2DDebugRenderer.h"

#include <algorithm>
#include <cassert>
#include <b2_math.h>
#include <b2_world.h>
#include <box2d.h>

const int32 VelocityIterations = 8;
const int32 PositionIterations = 3;

PhysicsWorld::PhysicsWorld(const Vector2& gravity)
    : world(b2World(b2Vec2(gravity.x, gravity.y))) {
    debugRenderer = std::make_unique<Box2DDebugRenderer>();
    world.SetDebugDraw(debugRenderer.get());
}

void PhysicsWorld::Step(float timeStep) {
    world.Step(timeStep, VelocityIterations, PositionIterations);

    for (const auto rb : rigidbodies) {
	const b2Vec2& position = rb->body->GetPosition();
	Actor* owner = rb->GetOwner();
	owner->SetPosition(Vector2(position.x, position.y));

	auto box = owner->GetComponent<BoxColliderComponent>();
	DebugRenderer::DrawRect(box->GetBox());
    }
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
	std::iter_swap(iter, rigidbodies.end() - 1);
	rigidbodies.pop_back();
    }
}
