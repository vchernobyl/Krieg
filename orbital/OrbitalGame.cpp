#include "OrbitalGame.h"
#include "Player.h"
#include "Orbit.h"

void OrbitalGame::LoadData() {
    new Player(this);
    new Orbit(this, Vector2::Zero, 10.0f);
}
