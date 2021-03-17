#pragma once

#include "Math.h"
#include "Game.h"
#include "InputSystem.h"
#include "Component.h"
#include <vector>
#include <cstdint>

class Actor {
public:
    enum ActorState {
	Active,
	Paused,
	Dead
    };

    Actor(class Game* g);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& v) { position = v; }

    void SetPositionX(float x) { position.x = x; }
    void SetPositionY(float y) { position.y = y; }

    void TranslateX(float x) { position.x += x; }
    void TranslateY(float y) { position.y += y; }
    void Translate(float x, float y) { position.x += x; position.y += y; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    float GetRotation() const { return rotation; }
    void SetRotation(float r) { rotation = r; }

    ActorState GetState() const { return actorState; }
    void SetState(ActorState s) { actorState = s; }

    bool IsStatic() const { return isStatic; }
    void SetIsStatic(bool isStatic) { this->isStatic = isStatic; }

    Vector2 GetForward() const { return Vector2(Math::Cos(rotation), -Math::Sin(rotation)); }

    class Game* GetGame() const { return game; }

    void ProcessInput(const InputState& inputState);
    virtual void ActorInput(const InputState& inputState);

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

    template <class T> T* GetComponent() {
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
    bool isStatic;
    std::vector<class Component*> components;
    class Game* game;
};
