#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      currentFrame(0.0f),
      animFps(24.0f) {}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    if (animTextures.size() > 0) {
	currentFrame += animFps * deltaTime;
	while (currentFrame >= animTextures.size()) {
	    currentFrame -= animTextures.size();
	}
	SetTexture(animTextures[static_cast<int>(currentFrame)]);
    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures) {
    animTextures = textures;
    if (animTextures.size() > 0) {
	currentFrame = 0.0f;
	SetTexture(animTextures[0]);
    }
}
