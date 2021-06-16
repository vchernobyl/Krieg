#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"
#include "Actor.h"
#include "Debug.h"
#include "Math.h"

#include <algorithm>
#include <cassert>
#include <b2_math.h>
#include <b2_world.h>

PhysicsWorld::PhysicsWorld(const Vector2& gravity)
    : world(b2World(b2Vec2(gravity.x, gravity.y))) {}

void PhysicsWorld::Step(float deltaTime) {
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
