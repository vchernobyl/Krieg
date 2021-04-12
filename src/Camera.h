#pragma once

#include "SDL.h"
#include "Math.h"

// TODO: Add world to screen calculation functions.
class Camera {
public:
    Camera(int viewportWidth, int viewportHeight);
    void MoveTo(Vector2 position) { this->position = position; }
    void TranslateX(float dx) { this->position.x += dx; }
    void TranslateY(float dy) { this->position.y += dy; }
    void Follow(class Actor* owner);
    void SetWorldSize(Vector2 worldSize) { this->worldSize = worldSize; }
    void ToScreenSpace(SDL_Rect& dst) const;
    const SDL_Rect& GetViewport() const { return viewport; }
    const Vector2& GetPosition() const { return position; }
private:
    int viewportWidth;
    int viewportHeight;
    SDL_Rect viewport;
    Vector2 position;
    Vector2 worldSize;
};
