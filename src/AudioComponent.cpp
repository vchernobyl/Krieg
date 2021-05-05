#include "AudioComponent.h"
#include "Actor.h"
#include "Game.h"
#include "AudioSystem.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

AudioComponent::~AudioComponent() {
    StopAllEvents();
}

void AudioComponent::Update(float deltaTime) {
    auto iter = events.begin();
    while (iter != events.end()) {
	if (!iter->IsValid()) {
	    iter = events.erase(iter);
	} else {
	    ++iter;
	}
    }
}

SoundEvent AudioComponent::PlayEvent(const std::string& name) {
    auto event = owner->GetGame()->GetAudioSystem()->PlayEvent(name);
    events.push_back(event);
    return event;
}

void AudioComponent::StopAllEvents() {
    for (auto& event : events) {
	event.Stop();
    }
    events.clear();
}
