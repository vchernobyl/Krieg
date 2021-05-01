#pragma once

#include "Math.h"
#include <vector>

class Game;
class InputState;
class Component;
class CollisionInfo;

class Actor {
public:
    enum ActorState {
	Active,
	Paused,
	Dead
    };

    Actor(Game* game);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& v) { position = v; }
    void Translate(const Vector2& v) { position.x += v.x; position.y += v.y; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    ActorState GetState() const { return actorState; }
    void SetState(ActorState s) { actorState = s; }
    void Destroy() { actorState = ActorState::Dead; }

    Game* GetGame() const { return game; }

    void ProcessInput(const InputState& inputState);
    virtual void ActorInput(const InputState& inputState);

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    virtual void OnCollisionEnter(const CollisionInfo& info) {}

    template <typename T> T* GetComponent() {
	for (auto component : components) {
	    if (dynamic_cast<T*>(component)) {
		return dynamic_cast<T*>(component);
	    }
	}
	return nullptr;
    }

private:
    ActorState actorState;
    Vector2 position;
    float scale;
    float rotation;
    std::vector<Component*> components;
    Game* game;
};
