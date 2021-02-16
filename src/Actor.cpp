#include "Actor.h"
#include "Math.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* g)
    : state(Active),
      position(Vector2(0.0f, 0.0f)),
      scale(1.0f),
      rotation(0.0f),
      game(g) {
    game->AddActor(this);
}

Actor::~Actor() {
    game->RemoveActor(this);
    while (!components.empty()) {
	delete components.back();
    }
}

void Actor::Update(float deltaTime) {
    if (state == Active) {
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
