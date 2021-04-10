#include "DebugRenderer.h"
#include "BoxColliderComponent.h"
#include "PhysicsWorld.h"
#include "Camera.h"
#include "SDL.h"

void DebugRenderer::Draw(SDL_Renderer* renderer) {
    for (auto collider : world->GetColliders()) {
	if (auto box = static_cast<BoxColliderComponent*>(collider)) {
	    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	    auto rect = box->GetBox();
	    auto collidable = SDL_Rect {
		static_cast<int>(rect.position.x),
		static_cast<int>(rect.position.y),
		static_cast<int>(rect.size.x),
		static_cast<int>(rect.size.y)
	    };
	    collidable.x -= camera->GetPosition().x;
	    collidable.y -= camera->GetPosition().y;
	    SDL_RenderDrawRect(renderer, &collidable);
	}
    }
}
