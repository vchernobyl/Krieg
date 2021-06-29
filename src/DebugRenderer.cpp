#include "DebugRenderer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Math.h"
#include "Game.h"

#include <SDL.h>
#include <cassert>

class DebugShape {
public:
    virtual ~DebugShape() {}
    virtual void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) = 0;
};

class DebugRect : public DebugShape {
public:
    DebugRect(float x, float y, float width, float height);
    void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) override;
private:
    float x, y;
    float width, height;
};

DebugRect::DebugRect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void DebugRect::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    int camX = static_cast<int>(camPos.x);
    int camY = static_cast<int>(camPos.y);

    SDL_Rect rect;
    rect.x = static_cast<int>(x) - camX;
    rect.y = static_cast<int>(y) - camY;
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);

    SDL_RenderDrawRect(renderer, &rect);
}

class DebugLine : public DebugShape {
public:
    DebugLine(float x1, float y1, float x2, float y2);
    void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) override;
private:
    float x1, y1;
    float x2, y2;
};

DebugLine::DebugLine(float x1, float y1, float x2, float y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

void DebugLine::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    int camX = static_cast<int>(camPos.x);
    int camY = static_cast<int>(camPos.y);
    SDL_RenderDrawLine(renderer, x1 - camX, y1 - camY, x2 - camX, y2 - camY);
}

std::vector<DebugShape*> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(float x, float y, float width, float height) {
    DebugShape* rect = new DebugRect(x, y, width, height);
    shapes.push_back(rect);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2) {
    float pixels = Game::UnitsToPixels;
    DebugShape* line = new DebugLine(x1 * pixels, y1 * pixels, x2 * pixels, y2 * pixels);
    shapes.push_back(line);
}

void DebugRenderer::Draw(Renderer* renderer) {
    SDL_Renderer* sdlRenderer = renderer->renderer;
    Vector2 camPos = renderer->GetCamera()->GetPosition();
    
    SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 0, 255);
    for (auto shape : shapes) {
	shape->Draw(sdlRenderer, camPos);
	delete shape;
    }

    shapes.clear();
    assert(shapes.empty());
}
