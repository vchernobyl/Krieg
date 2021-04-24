#include "Actor.h"
#include "Math.h"
#include "Game.h"
#include "Component.h"
#include "InputSystem.h"
#include <algorithm>

Actor::Actor(Game* game)
    : actorState(Active),
      position(Vector2::Zero),
      scale(1.0f),
      rotation(0.0f),
      game(game) {
    game->AddActor(this);
}

Actor::~Actor() {
    game->RemoveActor(this);
    while (!components.empty()) {
	delete components.back();
    }
}

void Actor::ProcessInput(const InputState& inputState) {
    if (actorState == Active) {
	for (auto comp : components) {
	    comp->ProcessInput(inputState);
	}
	ActorInput(inputState);
    }
}

void Actor::ActorInput(const InputState& inputState) {}

void Actor::Update(float deltaTime) {
    if (actorState == Active) {
	UpdateComponents(deltaTime);
	UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto component : components) {
	component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

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
