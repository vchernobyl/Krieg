#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder) :
    SpriteComponent(owner, drawOrder),
    scrollSpeed(0.0f) {}

void BGSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    for (auto& bg : bgTextures) {
	bg.offset.x += scrollSpeed * deltaTime;
	if (bg.offset.x < -screenSize.x) {
	    bg.offset.x = (bgTextures.size() - 1) * screenSize.x - 1;
	}
    }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer) {
    for (auto& bg : bgTextures) {
	SDL_Rect rect;
	rect.w = static_cast<int>(screenSize.x);
	rect.h = static_cast<int>(screenSize.y);
	rect.x = static_cast<int>(owner->GetPosition().x - rect.w / 2 + bg.offset.x);
	rect.y = static_cast<int>(owner->GetPosition().y - rect.h / 2 + bg.offset.y);
	SDL_RenderCopy(renderer, bg.texture, nullptr, &rect);
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures) {
    int count = 0;
    for (auto tex : textures) {
	BGTexture temp;
	temp.texture = tex;
	temp.offset.x = count * screenSize.x;
	temp.offset.y = 0;
	bgTextures.emplace_back(temp);
	count++;
    }
}
