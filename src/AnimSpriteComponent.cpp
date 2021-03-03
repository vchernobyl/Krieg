#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner)
    : SpriteComponent(owner),
      flip(SDL_FLIP_NONE),
      animNum(0), frameNum(0),
      frameTime(0.0f), animFPS(24.0f) {}

void AnimSpriteComponent::Update(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime > (1.0f / animFPS)) {
	frameNum += frameTime * animFPS;
	if (frameNum >= animData.frameInfo[animNum].numFrames) {
	    // Continue tomorrow from here.
	    if (animData.frameInfo[animNum].isLooping)
		frameNum = frameNum % animData.frameInfo[animNum].numFrames;
	}
	int imageNum = animData.frameInfo[animNum].startFrame + frameNum;
	SetTexture(animData.images[imageNum], flip);
	frameTime = Math::Fmod(frameTime, 1.0f / animFPS);
    }
}

void AnimSpriteComponent::ChangeAnim(int animNum, SDL_RendererFlip flip) {
    this->animNum = animNum;
    this->flip = flip;
    frameNum = 0;
    frameTime = 0.0f;
    int imageNum = animData.frameInfo[animNum].startFrame;
    SetTexture(animData.images[imageNum], flip);
}
