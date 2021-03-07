#include "BackgroundComponent.h"
#include "Actor.h"

static const int WorldWidth = 1280;
static const int WorldHeight = 960;
static const int CameraWidth = 1024;
static const int CameraHeight = 768;

BackgroundComponent::BackgroundComponent(Actor* owner, int updateOrder) :
    SpriteComponent(owner, updateOrder) {
    SetTexture(owner->GetGame()->GetTexture("assets/background.png"));
}

void BackgroundComponent::Draw(SDL_Renderer* renderer) {
    if (texture) {
	Vector2 pos = owner->GetPosition();
	SDL_Rect background { 0, 0, WorldWidth, WorldHeight };
	SDL_Rect camera {
	    static_cast<int>(owner->GetPosition().x - CameraWidth / 2),
	    static_cast<int>(owner->GetPosition().y - CameraHeight / 2),
	    CameraWidth,
	    CameraHeight
	};
	SDL_Log("camera.x = %d, camera.y = %d", camera.x, camera.y);	
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > WorldWidth - CameraWidth) camera.x = WorldWidth - CameraWidth;
	if (camera.y > WorldHeight - CameraHeight) camera.y = WorldHeight - CameraHeight;

	SDL_RenderCopy(renderer, texture, &camera, &background);
    }
}
