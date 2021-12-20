#pragma once

#include "Maths.h"

#include <vector>
#include <string>

class Game;
class Component;
struct InputState;

class Actor {
public:
    enum class State {
        Active,
        Paused,
        Dead
    };

    Actor(Game* game);
    virtual ~Actor();

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& position) { this->position = position; }

    float GetScale() const { return scale; }
    void SetScale(float scale) { this->scale = scale; }

    float GetRotation() const { return rotation; }
    void SetRotation(float rotation) { this->rotation = rotation; }

    Vector2 GetForward() const { return Vector2(Math::Cos(rotation), Math::Sin(rotation)); }

    State GetState() const { return state; }
    void SetState(State state) { this->state = state; }

    const std::string& GetTag() const { return tag; }
    void SetTag(const std::string& tag) { this->tag = tag; }

    Game* GetGame() const { return game; }

    void ProcessInput(const InputState& inputState);
    virtual void ActorInput(const InputState& inputState);

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    // TODO:: Add `void BeginContact(Contact&)` which will be called from physics world on contact.
    // This guy will first notify all of the components about the contact,
    // and notify the actor about the contact as well.
    // Very similar to how we process the input state.
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
    State state;

    Vector2 position;
    float scale;
    float rotation; // In radians
    std::string tag;

    std::vector<Component*> components;
    Game* game;
};
