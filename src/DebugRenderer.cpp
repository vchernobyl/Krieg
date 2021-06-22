#include "DebugRenderer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Math.h"

#include <SDL.h>
#include <cassert>

DebugRect::DebugRect(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

void DebugRect::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    SDL_Rect rect = { x - static_cast<int>(camPos.x), y - static_cast<int>(camPos.y), width, height };
    SDL_RenderDrawRect(renderer, &rect);
}

std::vector<DebugShape*> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(int x, int y, int width, int height) {
    DebugShape* rect = new DebugRect(x, y, width, height);
    shapes.push_back(rect);
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
