#include "Debug.h"
#include "Renderer.h"
#include "Camera.h"

std::vector<Rectangle> Debug::rects = {};
std::vector<std::pair<Vector2, Vector2> > Debug::lines = {};

void Debug::Draw(Renderer* renderer) {
    for (const auto& rect : rects) {
	auto sdlRenderer = renderer->GetSDLRenderer();
	SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 0, 255);
	auto sdlRect = SDL_Rect {
	    static_cast<int>(rect.position.x),
	    static_cast<int>(rect.position.y),
	    static_cast<int>(rect.size.x),
	    static_cast<int>(rect.size.y)
	};
	renderer->GetCamera()->ToScreenSpace(sdlRect);
	SDL_RenderDrawRect(sdlRenderer, &sdlRect);
    }

    for (auto line : lines) {
	auto start = line.first - renderer->GetCamera()->GetPosition();
	auto end = line.second - renderer->GetCamera()->GetPosition();

	SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer->GetSDLRenderer(), start.x, start.y, end.x, end.y);
    }
    
    rects.clear();
    lines.clear();
}

void Debug::DrawRect(const Rectangle& rect) {
#ifdef DEBUG
    rects.push_back(rect);
#endif
}

void Debug::DrawLine(const Vector2& start, const Vector2& end) {
#ifdef DEBUG
    lines.emplace_back(start, end);
#endif
}
