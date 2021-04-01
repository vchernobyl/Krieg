#include "DebugRenderer.h"
#include "BoxColliderComponent.h"
#include "PhysicsWorld.h"
#include "Camera.h"
#include "SDL.h"

void DebugRenderer::Draw(SDL_Renderer* renderer) {
    for (auto collider : world->GetColliders()) {
	if (auto box = static_cast<BoxColliderComponent*>(collider)) {
	    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	    auto rect = box->GetCollidable();
	    auto collidable = SDL_Rect { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
	    collidable.x -= camera->GetPosition().x;
	    collidable.y -= camera->GetPosition().y;
	    SDL_RenderDrawRect(renderer, &collidable);
	}
    }
}
