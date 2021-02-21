#include "AnimatedSpriteComponent.h"
#include "Math.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner)
    : SpriteComponent(owner),
      animNum(0), frameNum(0),
      frameTime(0.0f), animFPS(24.0f) {}

void AnimatedSpriteComponent::Update(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime > (1.0f / animFPS)) {
	frameNum += frameTime * animFPS;
	if (frameNum >= animData.frameInfo[animNum].numFrames) {
	    frameNum = frameNum % animData.frameInfo[animNum].numFrames;
	}
	int imageNum = animData.frameInfo[animNum].startFrame + frameNum;
	SetTexture(animData.images[imageNum]);
	frameTime = Math::Fmod(frameTime, 1.0f / animFPS);
    }
}

void AnimatedSpriteComponent::ChangeAnim(int num) {
    animNum = num;
    frameNum = 0;
    frameTime = 0.0f;
    int imageNum = animData.frameInfo[animNum].startFrame;
    SetTexture(animData.images[imageNum]);
}
