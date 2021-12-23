#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight) {
    orthoProjection = Matrix4::CreateOrtho(screenWidth, screenHeight, 0.0f, 1.0f);
}
    
void Camera::Update() {
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

bool Camera::IsBoxInView(const Vector2& boxPosition, const Vector2& size) {
    auto scaledScreenSize = Vector2(screenWidth, screenHeight) / scale;
    float minDistanceX = size.x / 2.0f + scaledScreenSize.x / 2.0f;
    float minDistanceY = size.y / 2.0f + scaledScreenSize.y / 2.0f;
    
    auto centerPos = boxPosition + size / 2.0f;
    auto distVec = boxPosition - position;
    
    float xDepth = minDistanceX - Math::Abs(distVec.x);
    float yDepth = minDistanceY - Math::Abs(distVec.y);

    if (xDepth > 0 && yDepth > 0) {
        return true;
    }

    return false;
}
