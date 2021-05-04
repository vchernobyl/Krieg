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

void SoundEvent::Stop(bool allowFadeOut) {}

void SoundEvent::SetPaused(bool pause) {}

void SoundEvent::SetVolume(float value) {}

void SoundEvent::SetPitch(float value) {}

void SoundEvent::SetParameter(const std::string& name, float value) {}

bool SoundEvent::GetPaused() const { return false; }

float SoundEvent::GetVolume() const { return 0; }

float SoundEvent::GetPitch() const { return 0; }

float SoundEvent::GetParameter(const std::string& name) { return 0; }
