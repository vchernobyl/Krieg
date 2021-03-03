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

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(Actor* owner);
    void SetAnimData(const AnimData& animData) { this->animData = animData; }
    void SetAnimFPS(float animFPS) { this->animFPS = animFPS; }
    void SetAnimFlip(SDL_RendererFlip flip) { this->flip = flip; }
    void Update(float deltaTime) override;
    void ChangeAnim(int animNum, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    AnimData animData;
    SDL_RendererFlip flip;
    int animNum, frameNum;
    float frameTime, animFPS;
};
