#include "Laser.h"
#include "Game.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Laser::Laser(Game* game)
    : Actor(game),
      deathTimer(1.0f) {
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("assets/Laser.png"));

    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(800.0f);

    circle = new CircleComponent(this);
    circle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime) {
    for (auto asteroid : GetGame()->GetAsteroids()) {
	if (Intersect(*circle, *(asteroid->GetCircle()))) {
	    SetState(Dead);
	    asteroid->SetState(Dead);
	    break;
	}
    }
}
