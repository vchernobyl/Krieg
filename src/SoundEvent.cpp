#include "SoundEvent.h"
#include "AudioSystem.h"

#include <fmod_studio.hpp>

SoundEvent::SoundEvent()
    : system(nullptr),
      ID(0) {}

SoundEvent::SoundEvent(AudioSystem* system, unsigned int id)
    : system(system),
      ID(id) {}

bool SoundEvent::IsValid() {
    return system && system->GetEventInstance(ID) != nullptr;
}

void SoundEvent::Restart() {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	event->start();
    }
}

void SoundEvent::Stop(bool allowFadeOut) {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
	    FMOD_STUDIO_STOP_ALLOWFADEOUT :
	    FMOD_STUDIO_STOP_IMMEDIATE;
	event->stop(mode);
    }
}

void SoundEvent::SetPaused(bool pause) {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	event->setPaused(pause);
    }
}

void SoundEvent::SetVolume(float value) {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	event->setVolume(value);
    }
}

void SoundEvent::SetPitch(float value) {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	event->setPitch(value);
    }
}

void SoundEvent::SetParameter(const std::string& name, float value) {
    const auto event = system ? system->GetEventInstance(ID) : nullptr;
    if (event) {
	event->setParameterByName(name.c_str(), value);
    }
}

bool SoundEvent::GetPaused() const { return false; }

float SoundEvent::GetVolume() const { return 0; }

float SoundEvent::GetPitch() const { return 0; }

float SoundEvent::GetParameter(const std::string& name) { return 0; }
