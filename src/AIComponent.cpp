#include "AIComponent.h"
#include "AIState.h"
#include "Actor.h"
#include <SDL/SDL_log.h>

AIComponent::AIComponent(class Actor* owner)
    : Component(owner), currentState(nullptr) {
}

void AIComponent::Update(float deltaTime) {
    if (currentState) {
        currentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string& name) {
    if (currentState) {
        currentState->OnExit();
    }

    auto iter = stateMap.find(name);
    if (iter != stateMap.end()) {
        currentState = iter->second;
        currentState->OnEnter();
    } else {
        SDL_Log("Could not find AIState %s in state map", name.c_str());
        currentState = nullptr;
    }
}

void AIComponent::RegisterState(AIState* state) {
    stateMap.emplace(state->GetName(), state);
}
