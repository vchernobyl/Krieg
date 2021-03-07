#include "BackgroundComponent.h"
#include "Actor.h"

static const int ScreenWidth = 1280;
static const int ScreenHeight = 960;

BackgroundComponent::BackgroundComponent(Actor* owner, int updateOrder) :
    SpriteComponent(owner, updateOrder) {
    SetTexture(owner->GetGame()->GetTexture("assets/background.png"));
}

void BackgroundComponent::Draw(SDL_Renderer* renderer) {
    if (texture) {	
	SDL_Rect rect { 0, 0, ScreenWidth, ScreenHeight };
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}
