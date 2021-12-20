#include "SpaceGame.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Enemy.h"
#include "HUD.h"
#include "DebugUI.h"
#include "AudioSystem.h"

SpaceGame::SpaceGame() : Game() {
}

void SpaceGame::LoadData() {
    GetAudioSystem()->LoadBank("data/audio/Master.strings.bank");
    GetAudioSystem()->LoadBank("data/audio/Master.bank");

    new Ship(this);
    
    auto e1 = new Enemy(this);
    e1->SetPosition(Vector2(15.0f, -3.5f));
    
    auto e2 = new Enemy(this);
    e2->SetPosition(Vector2(-5.5f, 12.0f));
    
    auto e3 = new Enemy(this);
    e3->SetPosition(Vector2(12.3f, 2.5f));

    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; i++) {
        new Asteroid(this);
    }

    new DebugUI(this);
    new HUD(this);
}
