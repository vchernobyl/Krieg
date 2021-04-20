#include "DebugRenderer.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PhysicsWorld.h"
#include "Camera.h"
#include "SDL.h"

void DebugRenderer::Draw(Renderer* renderer) {
    for (auto collider : world->GetColliders()) {
	if (auto box = static_cast<BoxColliderComponent*>(collider)) {
	    SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
	    auto rect = box->GetBox();
	    auto collidable = SDL_Rect {
		static_cast<int>(rect.position.x),
		static_cast<int>(rect.position.y),
		static_cast<int>(rect.size.x),
		static_cast<int>(rect.size.y)
	    };
	    renderer->GetCamera()->ToScreenSpace(collidable);
	    SDL_RenderDrawRect(renderer->GetSDLRenderer(), &collidable);
	}
    }
}
