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
    MoveTo(target);
}
