#include "OrbitalGame.h"

void OrbitalGame::LoadData() {
    auto owner = new Actor(this);
    auto sprite = new SpriteComponent(owner);
    sprite->SetTexture(GetRenderer()->GetTexture("data/textures/Ship.png"));
}
