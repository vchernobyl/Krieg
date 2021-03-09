#include "Camera.h"

Camera::Camera(int viewportWidth, int viewportHeight)
    : viewportWidth(viewportWidth),
      viewportHeight(viewportHeight) {
    viewport = SDL_Rect {
	static_cast<int>(position.x),
	static_cast<int>(position.y),
	viewportWidth,
	viewportHeight
    };
}

void Camera::Follow(Actor* owner) {
    Vector2 target = owner->GetPosition();
    target.x -= viewportWidth / 2;
    target.y -= viewportHeight / 2;

    if (target.x < 0) target.x = 0;
    if (target.y < 0) target.y = 0;
    if (target.x > worldSize.x - viewportWidth) target.x = worldSize.x - viewportWidth;
    if (target.y > worldSize.y - viewportHeight) target.y = worldSize.y - viewportHeight;

    MoveTo(target);
}
