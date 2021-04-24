#pragma once

#include "Math.h"
#include <vector>

class Actor {
public:
    enum ActorState {
	Active,
	Paused,
	Dead
    };

    Actor(class Game* game);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& v) { position = v; }
    void SetPositionX(float x) { position.x = x; }
    void SetPositionY(float y) { position.y = y; }

    void Translate(float x, float y) { position.x += x; position.y += y; }
    void Translate(const Vector2& v) { position.x += v.x; position.y += v.y; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    float GetRotation() const { return rotation; }
    void SetRotation(float r) { rotation = r; }

    ActorState GetState() const { return actorState; }
    void SetState(ActorState s) { actorState = s; }

    bool IsStatic() const { return isStatic; }
    void SetIsStatic(bool isStatic) { this->isStatic = isStatic; }

    class Game* GetGame() const { return game; }

    void ProcessInput(const class InputState& inputState);
    virtual void ActorInput(const class InputState& inputState);

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
