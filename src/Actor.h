#pragma once

#include "Math.h"

#include <vector>

class Game;
class Component;
class ColliderComponent;
struct CollisionInfo;
struct InputState;

class Actor {
public:
    enum class ActorState {
	Active,
	Paused,
	Dead
    };

    Actor(Game* game);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& v) { position = v; recomputeWorldTransform = true; }

    float GetScale() const { return scale; }
    void SetScale(float scale) { this->scale = scale; recomputeWorldTransform = true; }

    float GetRotation() const { return rotation; }
    void SetRotation(float rotation) { this->rotation = rotation; recomputeWorldTransform = true; }

    void ComputeWorldTransform();
    const Matrix4& GetWorldTransform() const { return worldTransform; }

    Vector2 GetForward() const { return Vector2(Math::Cos(rotation), Math::Sin(rotation)); }

    ActorState GetState() const { return actorState; }
    void SetState(ActorState s) { actorState = s; }

    Game* GetGame() const { return game; }

    void ProcessInput(const InputState& inputState);
    virtual void ActorInput(const InputState& inputState);

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    virtual void OnBeginContact(const struct Contact& contact) {}

    template <typename T> T* GetComponent() {
	for (auto component : components) {
	    if (auto target = dynamic_cast<T*>(component)) {
		return target;
	    }
	}
	return nullptr;
    }

private:
    ActorState actorState;

    Matrix4 worldTransform;
    Vector2 position;
    float scale;
    float rotation; // In radians
    bool recomputeWorldTransform;

    std::vector<Component*> components;
    Game* game;
};
