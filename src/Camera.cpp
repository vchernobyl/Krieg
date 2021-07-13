#include "Camera.h"
#include "Actor.h"
#include "Game.h"

Camera::Camera(int viewportWidth, int viewportHeight)
    : viewportWidth(viewportWidth),
      viewportHeight(viewportHeight) {}

void Camera::Follow(Actor* owner) {
    Vector2 target = owner->GetPosition();
    target.x -= viewportWidth / 2;
    target.y -= viewportHeight / 2;

    if (target.x < 0) target.x = 0;
    if (target.y < 0) target.y = 0;
    if (target.x > worldSize.x - viewportWidth) target.x = worldSize.x - viewportWidth;
    if (target.y > worldSize.y - viewportHeight) target.y = worldSize.y - viewportHeight;

    SetPosition(target);
}

void Camera::ToScreenSpace(SDL_Rect& dst) const {
    dst.x -= position.x * Game::UnitsToPixels;
    dst.y -= position.y * Game::UnitsToPixels;
}
