#pragma once

#include "Actor.h"
#include "Component.h"
#include "SpriteComponent.h"
#include <vector>

struct AnimFrameData {
    int startFrame;
    int numFrames;
};

struct AnimData {
    std::vector<SDL_Texture*> images;
    std::vector<AnimFrameData> frameInfo;
};

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(Actor* owner);
    void SetAnimData(const AnimData& animData) { this->animData = animData; }
    void SetAnimFPS(float animFPS) { this->animFPS = animFPS; }
    void Update(float deltaTime) override;
    void ChangeAnim(int num);
private:
    AnimData animData;
    int animNum, frameNum;
    float frameTime, animFPS;
};
