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
    virtual void Draw(SDL_Renderer* renderer, const Vector2& camPos) = 0;
};

class DebugRect : public DebugShape {
public:
    DebugRect(float x, float y, float width, float height);
    void Draw(SDL_Renderer* renderer, const Vector2& camPos) override;
private:
    float x, y;
    float width, height;
};

DebugRect::DebugRect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

void DebugRect::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    SDL_Rect rect;
    rect.x = static_cast<int>(x - camPos.x);
    rect.y = static_cast<int>(y - camPos.y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);

    SDL_RenderDrawRect(renderer, &rect);
}

class DebugLine : public DebugShape {
public:
    DebugLine(float x1, float y1, float x2, float y2);
    void Draw(SDL_Renderer* renderer, const Vector2& camPos) override;
private:
    float x1, y1;
    float x2, y2;
};

DebugLine::DebugLine(float x1, float y1, float x2, float y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

void DebugLine::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    SDL_RenderDrawLine(renderer,
		       static_cast<int>(x1 - camPos.x),
		       static_cast<int>(y1 - camPos.y),
		       static_cast<int>(x2 - camPos.x),
		       static_cast<int>(y2 - camPos.y));
}

std::vector<std::pair<DebugShape*, Color>> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(float x, float y, float width, float height, Color color) {
    const float toPixels = Game::UnitsToPixels;
    DebugShape* rect = new DebugRect(x * toPixels, y * toPixels, width * toPixels, height * toPixels);
    shapes.emplace_back(rect, color);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2, Color color) {
    const float toPixels = Game::UnitsToPixels;
    DebugShape* line = new DebugLine(x1 * toPixels, y1 * toPixels, x2 * toPixels, y2 * toPixels);
    shapes.emplace_back(line, color);
}

void DebugRenderer::Draw(Renderer* renderer) {
    SDL_Renderer* sdlRenderer = renderer->renderer;
    Vector2 camPos = renderer->GetCamera()->GetPosition() * Game::UnitsToPixels;
    
    for (auto pair : shapes) {
	const auto color = pair.second;
	SDL_SetRenderDrawColor(sdlRenderer, color.r, color.g, color.b, color.a);

	const auto shape = pair.first;
	shape->Draw(sdlRenderer, camPos);
	delete shape;
    }

    shapes.clear();
    assert(shapes.empty());
}
