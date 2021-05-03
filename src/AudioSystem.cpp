#include "AudioSystem.h"
#include "Game.h"

#include <fmod_studio.hpp>
#include <fmod_errors.h>

AudioSystem::AudioSystem(Game* game) : game(game), system(nullptr) {}

bool AudioSystem::Initialize() {
    FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);

    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&system);
    if (result != FMOD_OK) {
	SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
	return false;
    }

    result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
	SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
	return false;
    }
    
    return true;
}

void AudioSystem::Shutdown() {
    if (system) {
	system->release();
    }
}
    
void AudioSystem::Update(float deltaTime) {
    system->update();
}
