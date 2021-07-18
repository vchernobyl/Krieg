#include "Camera.h"
#include "Actor.h"
#include "Game.h"

Camera::Camera(int viewportWidth, int viewportHeight)
    : viewportWidth(viewportWidth),
      viewportHeight(viewportHeight) {}

void Camera::CenterAt(const Vector2& position) {
    auto target = position - Vector2(viewportWidth / 2, viewportHeight / 2);

    if (target.x < 0) target.x = 0;
    if (target.y < 0) target.y = 0;
    if (target.x > worldSize.x - viewportWidth) target.x = worldSize.x - viewportWidth;
    if (target.y > worldSize.y - viewportHeight) target.y = worldSize.y - viewportHeight;

    SetPosition(target);
}
