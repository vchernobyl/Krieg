#include "AudioSystem.h"
#include "Game.h"
#include <fmod_studio.h>

AudioSystem::AudioSystem(Game* game) : game(game) {}

AudioSystem::~AudioSystem() {}

bool AudioSystem::Initialize() {
    return false;
}

void AudioSystem::Shutdown() {}
    
