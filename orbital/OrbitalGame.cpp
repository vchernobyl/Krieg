#include "OrbitalGame.h"
#include "Player.h"
#include "Orbit.h"

void OrbitalGame::LoadData() {
    auto audioSystem = GetAudioSystem();
    audioSystem->LoadBank("data/audio/Master.strings.bank");
    audioSystem->LoadBank("data/audio/Master.bank");
    
    new Player(this);
    new Orbit(this, Vector2::Zero, 10.0f);
    new DebugUI(this);
}
