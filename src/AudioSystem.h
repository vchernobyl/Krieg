#pragma once

#include <unordered_map>
#include <string>

// Forward declaration of the FMOD namespaces.
namespace FMOD {
    class System;
    namespace Studio {
	class Bank;
	class EventDescription;
	class EventInstance;
	class System;
	class Bus;
    }
};

class Game;

class AudioSystem {
public:
    AudioSystem(Game* game);
    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);

    void LoadBank(const std::string& name);
    void UnloadBank(const std::string& name);
    void UnloadAllBanks();
private:
    Game* game;
    FMOD::Studio::System* system;
    std::unordered_map<std::string, FMOD::Studio::Bank*> banks;
    std::unordered_map<std::string, FMOD::Studio::EventDescription*> events;
};
