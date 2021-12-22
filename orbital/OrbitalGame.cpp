#include "OrbitalGame.h"
#include "Player.h"
#include "Planet.h"

void OrbitalGame::LoadContent() {
    auto audioSystem = GetAudioSystem();
    audioSystem->LoadBank("data/audio/Master.strings.bank");
    audioSystem->LoadBank("data/audio/Master.bank");
    
    new Player(this);
    new Planet(this, Vector2::Zero, 10.0f);
    new DebugUI(this);

    GetRenderer()->SetClearColor(Color::Gray);
}
