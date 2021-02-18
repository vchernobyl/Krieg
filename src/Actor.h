#pragma once

#include "Math.h"
#include "Game.h"
#include "Component.h"
#include <vector>
#include <cstdint>

class Actor {
public:
    enum State { Active, Paused, Dead };

    Actor(class Game* g);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& v) { position = v; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    float GetRotation() const { return rotation; }
    void SetRotation(float r) { rotation = r; }

    State GetState() const { return state; }
    void SetState(State s) { state = s; }

    Vector2 GetForward() const { return Vector2(Math::Cos(rotation), -Math::Sin(rotation)); }

    class Game* GetGame() const { return game; }

    void ProcessInput(const uint8_t* keyState);
    virtual void ActorInput(const uint8_t* keyState);

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    State state;
    Vector2 position;
    float scale;
    float rotation;
    std::vector<class Component*> components;
    class Game* game;
};
