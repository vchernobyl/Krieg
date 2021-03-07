#pragma once

#include "Actor.h"
#include "Component.h"
#include "SpriteComponent.h"
#include <vector>

struct AnimFrameData {
    int startFrame;
    int numFrames;
    int isLooping;
};

struct AnimData {
    std::vector<SDL_Texture*> images;
    std::vector<AnimFrameData> frameInfo;
};

enum AnimDirection {
    Left = SDL_FLIP_HORIZONTAL,
    Right = SDL_FLIP_NONE
};

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(Actor* owner);
    void SetAnimData(const AnimData& animData) { this->animData = animData; }
    void SetAnimFPS(float animFPS) { this->animFPS = animFPS; }
    void Update(float deltaTime) override;
    void ChangeAnim(int animNum, AnimDirection direction = Right);
    void SetDirection(AnimDirection direction);
    bool Finished(int animNum);
private:
    AnimData animData;
    AnimDirection direction;
    int animNum, frameNum;
    float frameTime, animFPS;
};
