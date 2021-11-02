#include "Actor.h"
#include "Math.h"
#include "Game.h"
#include "Component.h"
#include "InputSystem.h"

#include <algorithm>

Actor::Actor(Game* game)
    : state(State::Active),
      position(Vector2::Zero),
      scale(1.0f),
      rotation(0.0f),
      game(game),
      recomputeWorldTransform(true) {
    game->AddActor(this);
}

Actor::~Actor() {
    game->RemoveActor(this);
    while (!components.empty()) {
        delete components.back();
    }
}

void Actor::ProcessInput(const InputState& inputState) {
    if (state == State::Active) {
        for (auto comp : components) {
            comp->ProcessInput(inputState);
        }
        ActorInput(inputState);
    }
}

void Actor::ActorInput(const InputState& inputState) {}

void Actor::Update(float deltaTime) {
    if (state == State::Active) {
        ComputeWorldTransform();
        
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);

        ComputeWorldTransform();
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto component : components) {
        component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::ComputeWorldTransform() {
    if (recomputeWorldTransform) {
        recomputeWorldTransform = false;

        worldTransform = Matrix4::CreateScale(scale);
        worldTransform *= Matrix4::CreateRotationZ(rotation);
        worldTransform *= Matrix4::CreateTranslation(Vector3(position.x, position.y, 0.0f));

        for (auto component : components) {
            component->OnUpdateWorldTransform();
        }
    }
}

void Actor::AddComponent(Component* component) {
    int order = component->GetUpdateOrder();
    auto iter = components.begin();
    while (iter != components.end() && order > (*iter)->GetUpdateOrder()) {
        ++iter;
    }
    components.insert(iter, component);
}
            
void Actor::RemoveComponent(Component* component) {
    auto iter = std::find(components.begin(), components.end(), component);
    if (iter != components.end()) {
        components.erase(iter);
    }
}
