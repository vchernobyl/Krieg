#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "Texture.h"
#include "Maths.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      animNum(0),
      frameNum(0),
      frameTime(0.0f),
      animFPS(24.0f) {}

void AnimSpriteComponent::Update(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime > (1.0f / animFPS)) {
        frameNum += frameTime * animFPS;
        if (frameNum >= animData.frameInfo[animNum].numFrames) {
            if (animData.frameInfo[animNum].isLooping) {
                frameNum = frameNum % animData.frameInfo[animNum].numFrames;
            } else {
                frameNum = animData.frameInfo[animNum].numFrames - 1;
            }
        }
        int imageNum = animData.frameInfo[animNum].startFrame + frameNum;
        SetTexture(animData.images[imageNum]);
        frameTime = Math::Mod(frameTime, 1.0f / animFPS);
    }
}

void AnimSpriteComponent::ChangeAnim(int animNum) {
    this->animNum = animNum;
    frameNum = 0;
    frameTime = 0.0f;
    int imageNum = animData.frameInfo[animNum].startFrame;
    SetTexture(animData.images[imageNum]);
}

bool AnimSpriteComponent::Finished(int animNum) {
    if (this->animNum == animNum) {
        return frameNum >= animData.frameInfo[animNum].numFrames;
    }
    return false;
}
