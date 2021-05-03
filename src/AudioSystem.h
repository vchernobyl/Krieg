#pragma once

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
private:
    Game* game;
    FMOD::Studio::System* system;
};
