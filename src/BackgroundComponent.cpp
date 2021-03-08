#include "BackgroundComponent.h"
#include "InputSystem.h"
#include "Actor.h"

static const int WorldWidth = 1728;
static const int WorldHeight = 1080;
static const int CameraWidth = 1024;
static const int CameraHeight = 768;

BackgroundComponent::BackgroundComponent(Actor* owner, int updateOrder)
    : SpriteComponent(owner, updateOrder),
      camera({ 0, 0, CameraWidth, CameraHeight }),
      background({ 0, 0, WorldWidth, WorldHeight }) {
    SetTexture(owner->GetGame()->GetTexture("assets/background.png"));
}

void BackgroundComponent::ProcessInput(const InputState& input) {
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_D)) {
	camera.x += 50;
    }
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_A)) {
	camera.x -= 50;
    }
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_S)) {
	camera.y += 50;
    }
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_W)) {
	camera.y -= 50;
    }
    if (camera.x < 0) camera.x = 0;
    if (camera.x > WorldWidth - CameraWidth) camera.x = WorldWidth - CameraWidth;
    if (camera.y < 0) camera.y = 0;
    if (camera.y > WorldHeight - CameraHeight) camera.y = WorldHeight - CameraHeight;
}    

void BackgroundComponent::Draw(SDL_Renderer* renderer) {
    if (texture) {
	SDL_Rect background { 0, 0, WorldWidth, WorldHeight };
	SDL_RenderCopy(renderer, texture, &camera, &background);
    }
}
