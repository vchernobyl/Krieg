#pragma once

#include "SDL.h"
#include "Math.h"
#include "Actor.h"

class Camera {
public:
    Camera(int viewportWidth, int viewportHeight);
    void MoveTo(Vector2 position) { this->position = position; }
    void TranslateX(float dx) { this->position.x += dx; }
    void TranslateY(float dy) { this->position.y += dy; }
    void Follow(class Actor* owner);
    const SDL_Rect& GetViewport() const { return viewport; }
    const Vector2& GetPosition() const { return position; }
private:
    int viewportWidth;
    int viewportHeight;
    SDL_Rect viewport;
    Vector2 position;
};
