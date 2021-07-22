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
    : x(x * Game::UnitsToPixels),
      y(y * Game::UnitsToPixels),
      width(width * Game::UnitsToPixels),
      height(height * Game::UnitsToPixels) {}

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
    : x1(x1 * Game::UnitsToPixels),
      y1(y1 * Game::UnitsToPixels),
      x2(x2 * Game::UnitsToPixels),
      y2(y2 * Game::UnitsToPixels) {}

void DebugLine::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    SDL_RenderDrawLine(renderer,
		       static_cast<int>(x1 - camPos.x),
		       static_cast<int>(y1 - camPos.y),
		       static_cast<int>(x2 - camPos.x),
		       static_cast<int>(y2 - camPos.y));
}

class DebugCircle : public DebugShape {
public:
    DebugCircle(float centerX, float centerY, float radius);
    void Draw(SDL_Renderer* renderer, const Vector2& camPos) override;
private:
    float centerX, centerY;
    float radius;
};

DebugCircle::DebugCircle(float centerX, float centerY, float radius)
    : centerX(centerX * Game::UnitsToPixels),
      centerY(centerY * Game::UnitsToPixels),
      radius(radius * Game::UnitsToPixels) {}

void DebugCircle::Draw(SDL_Renderer* renderer, const Vector2& camPos) {
    const float diameter = (radius * 2);

    float x = (radius - 1);
    float y = 0.0f;
    float tx = 1.0f;
    float ty = 1.0f;
    float error = (tx - diameter);

    while (x >= 0) {
	SDL_RenderDrawPoint(renderer, centerX + x - camPos.x, centerY - y - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX + x - camPos.x, centerY + y - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX - x - camPos.x, centerY - y - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX - x - camPos.x, centerY + y - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX + y - camPos.x, centerY - x - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX + y - camPos.x, centerY + x - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX - y - camPos.x, centerY - x - camPos.y);
	SDL_RenderDrawPoint(renderer, centerX - y - camPos.x, centerY + x - camPos.y);

	if (error <= 0.0f) {
	    ++y;
	    error += ty;
	    ty += 2.0f;
	}

	if (error > 0.0f) {
	    --x;
	    tx += 2.0f;
	    error += (tx - diameter);
	}
    }
}

std::vector<std::pair<DebugShape*, Color>> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(float x, float y, float width, float height, Color color) {
    shapes.emplace_back(new DebugRect(x, y, width, height), color);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2, Color color) {
    shapes.emplace_back(new DebugLine(x1, y1, x2, y2), color);
}

void DebugRenderer::DrawCircle(float centerX, float centerY, float radius, Color color) {
    shapes.emplace_back(new DebugCircle(centerX, centerY, radius), color);
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
