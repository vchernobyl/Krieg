#pragma once

#include "SpriteComponent.h"
#include <vector>

struct AnimFrameData {
    int startFrame;
    int numFrames;
    int isLooping;
};

struct AnimData {
    std::vector<class Texture*> images;
    std::vector<AnimFrameData> frameInfo;
};

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
    void SetAnimData(const AnimData& animData) { this->animData = animData; }
    void SetAnimFPS(float animFPS) { this->animFPS = animFPS; }
    void Update(float deltaTime) override;
    void ChangeAnim(int animNum);
    bool Finished(int animNum);
private:
    AnimData animData;
    int animNum, frameNum;
    float frameTime, animFPS;
};
