#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner)
    : SpriteComponent(owner),
      direction(Right),
      animNum(0), frameNum(0),
      frameTime(0.0f), animFPS(24.0f) {}

void AnimSpriteComponent::Update(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime > (1.0f / animFPS)) {
	frameNum += frameTime * animFPS;
	if (frameNum >= animData.frameInfo[animNum].numFrames) {
	    if (animData.frameInfo[animNum].isLooping) {
		frameNum = frameNum % animData.frameInfo[animNum].numFrames;
	    } else {
		return;
	    }
	}
	int imageNum = animData.frameInfo[animNum].startFrame + frameNum;
	SetTexture(animData.images[imageNum], (SDL_RendererFlip) direction);
	frameTime = Math::Fmod(frameTime, 1.0f / animFPS);
    }
}

void AnimSpriteComponent::ChangeAnim(int animNum, AnimDirection direction) {
    this->animNum = animNum;
    this->direction = direction;
    frameNum = 0;
    frameTime = 0.0f;
    int imageNum = animData.frameInfo[animNum].startFrame;
    SetTexture(animData.images[imageNum], (SDL_RendererFlip) direction);
}

bool AnimSpriteComponent::Finished(int animNum) {
    if (this->animNum == animNum) {
	return frameNum >= animData.frameInfo[animNum].numFrames;
    }
    return false;
}
