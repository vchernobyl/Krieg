#include "Debug.h"
#include "Renderer.h"
#include "Camera.h"

std::vector<Rectangle> Debug::rects = {};

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

    rects.clear();
}

void Debug::DrawRect(const Rectangle& rect) {
#ifdef DEBUG
    rects.push_back(rect);
#endif
}
