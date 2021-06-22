#include "DebugRenderer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Math.h"

#include <SDL.h>
#include <cassert>

DebugRect::DebugRect(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

void DebugRect::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    int camX = static_cast<int>(camPos.x);
    int camY = static_cast<int>(camPos.y);
    SDL_Rect rect = { x - camX, y - camY, width, height };
    SDL_RenderDrawRect(renderer, &rect);
}

DebugLine::DebugLine(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

void DebugLine::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    int camX = static_cast<int>(camPos.x);
    int camY = static_cast<int>(camPos.y);
    SDL_RenderDrawLine(renderer, x1 - camX, y1 - camY, x2 - camX, y2 - camY);
}

std::vector<DebugShape*> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(int x, int y, int width, int height) {
    DebugShape* rect = new DebugRect(x, y, width, height);
    shapes.push_back(rect);
}

void DebugRenderer::DrawLine(int x1, int y1, int x2, int y2) {
    DebugShape* line = new DebugLine(x1, y1, x2, y2);
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
