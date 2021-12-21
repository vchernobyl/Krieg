#include "Orbit.h"

Orbit::Orbit(Game* game, const Vector2& center, float radius)
    : Actor(game), center(center), radius(radius) {
    SetTag("Orbit");
}

void Orbit::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(center, radius, Color::Yellow);
}
