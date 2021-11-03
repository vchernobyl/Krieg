#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight) {
    orthoProjection = Matrix4::CreateOrtho(screenWidth, screenHeight, 0.0f, 1.0f);
}
    
void Camera::Update(float deltaTime) {
    if (needsUpdate) {
        needsUpdate = false;

        // Looks like it's working correctly, but I'm not sure whether the
        // multiplication order is correct or just an accident.
        view = Matrix4::CreateTranslation(Vector3(-position.x, -position.y, 0.0f));
        view *= Matrix4::CreateScale(scale);
        view *= orthoProjection;
    }
}

Vector2 Camera::ScreenToWorld(const Vector2& screenPoint) {
    // Invert the y coords.
    auto worldPoint = Vector2(screenPoint.x, screenHeight - screenPoint.y);

    // Make (0, 0) to be at the center of the screen.
    worldPoint -= Vector2(screenWidth / 2.0f, screenHeight / 2.0f);
    worldPoint /= scale;
    worldPoint += position;
    
    return worldPoint;
}
