#include "DebugRenderer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Math.h"

#include <SDL.h>
#include <cassert>

std::vector<Rectangle> DebugRenderer::rects = {};

void DebugRenderer::DrawRect(const Rectangle& rect) {
    rects.push_back(rect);
}

void DebugRenderer::Draw(Renderer* renderer) {
    SDL_Renderer* sdlRenderer = renderer->renderer;
    Vector2 cameraPosition = renderer->GetCamera()->GetPosition();
    
    for (const auto& rect : rects) {
	SDL_Rect sdlRect = {
	    static_cast<int>(rect.position.x - cameraPosition.x),
	    static_cast<int>(rect.position.y - cameraPosition.y),
	    static_cast<int>(rect.size.x),
	    static_cast<int>(rect.size.y)
	};
	SDL_SetRenderDrawColor(sdlRenderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(sdlRenderer, &sdlRect);
    }

    rects.clear();
    assert(rects.empty());
}
