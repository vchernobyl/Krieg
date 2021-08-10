#include "AudioSystem.h"
#include "Game.h"

#include <SDL.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

unsigned int AudioSystem::nextID = 0;

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
    
    LoadBank("data/Master.strings.bank");
    LoadBank("data/Master.bank");
	
    return true;
}

void AudioSystem::Shutdown() {
    UnloadAllBanks();
    if (system) {
	system->release();
    }
}
    
void AudioSystem::Update(float deltaTime) {
    std::vector<unsigned int> done;

    for (const auto& iter : eventInstances) {
	FMOD::Studio::EventInstance* e = iter.second;
	FMOD_STUDIO_PLAYBACK_STATE state;
	e->getPlaybackState(&state);

	if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
	    e->release();
	    done.push_back(iter.first);
	}
    }

    for (const auto id : done) {
	eventInstances.erase(id);
    }

    system->update();
}

void AudioSystem::LoadBank(const std::string& name) {
    // Prevent double-loading.
    if (banks.find(name) != banks.end()) {
	return;
    }

    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = system->loadBankFile(name.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

    const int maxPathLength = 512;
    if (result == FMOD_OK) {
	banks.emplace(name, bank);
	bank->loadSampleData();
	
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
	    std::vector<FMOD::Studio::EventDescription*> bankEvents(numEvents);
	    bank->getEventList(bankEvents.data(), numEvents, &numEvents);
	    char eventName[maxPathLength];
	 
	    for (int i = 0; i < numEvents; i++) {
		FMOD::Studio::EventDescription* e = bankEvents[i];
		e->getPath(eventName, maxPathLength, nullptr);
		events.emplace(eventName, e);
	    }
	}
    }
}
	
void AudioSystem::UnloadBank(const std::string& name) {
    // Ignore if not loaded.
    auto iter = banks.find(name);
    if (iter == banks.end()) {
	return;
    }

    FMOD::Studio::Bank* bank = iter->second;
    int numEvents = 0;
    bank->getEventCount(&numEvents);
    if (numEvents > 0) {
	std::vector<FMOD::Studio::EventDescription*> bankEvents(numEvents);
	bank->getEventList(bankEvents.data(), numEvents, &numEvents);
	char eventName[512];

	for (int i = 0; i < numEvents; i++) {
	    FMOD::Studio::EventDescription* e = bankEvents[i];
	    e->getPath(eventName, 512, nullptr);
	    auto eventIter = events.find(eventName);
	    if (eventIter != events.end()) {
		events.erase(eventIter);
	    }
	}
    }

    bank->unloadSampleData();
    bank->unload();
    banks.erase(iter);
}

void AudioSystem::UnloadAllBanks() {
    for (const auto& iter : banks) {
	iter.second->unloadSampleData();
	iter.second->unload();
    }

    banks.clear();
    events.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name) {
    unsigned int retID = 0;
    const auto iter = events.find(name);
    
    if (iter != events.end()) {
	FMOD::Studio::EventInstance* event = nullptr;
	iter->second->createInstance(&event);
	if (event) {
	    event->start();
	    nextID++;
	    retID = nextID;
	    eventInstances.emplace(retID, event);
	}
    }

    return SoundEvent(this, retID);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id) {
    FMOD::Studio::EventInstance* event = nullptr;
    const auto iter = eventInstances.find(id);
    if (iter != eventInstances.end()) {
	event = iter->second;
    }
    return event;
}
