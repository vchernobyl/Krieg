#include "SpriteAnimation.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include <cassert>
#include <utility>

void Animation::AddFrame(int textureID, int x, int y, int width, int height, float frameTime) {
    FrameData frame;
    frame.id = textureID;
    frame.x = x;
    frame.y = y;
    frame.width = width;
    frame.height = height;
    frame.displayTimeSeconds = frameTime;
    frames.push_back(frame);
}

const Animation::FrameData* Animation::GetCurrentFrame() const {
    if (frames.size() > 0) {
        return &frames[currentFrameIndex];
    }
    return nullptr;
}

bool Animation::UpdateFrame(float deltaTime) {
    if (frames.size() > 0) {
        currentFrameTime += deltaTime;
        if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds) {
            currentFrameTime = 0.0f;
            currentFrameIndex = (currentFrameIndex + 1) % frames.size();
            return true;
        }
    }
    return false;
}

void Animation::Reset() {
    currentFrameIndex = 0;
    currentFrameTime = 0.0f;
}

SpriteAnimation::SpriteAnimation(Actor* owner, Texture* sheet) : Component(owner) {
    sprite = new SpriteComponent(owner);
    sprite->SetTexture(sheet);
    assert(sprite);
}

void SpriteAnimation::Update(float deltaTime) {
    if (currentAnimation == nullptr) return;

    bool frameChanged = currentAnimation->UpdateFrame(deltaTime);
    if (frameChanged) {
        const auto& frame = currentAnimation->GetCurrentFrame();
        sprite->SetRect(frame->x, frame->y, frame->width, frame->height);
    }
}

void SpriteAnimation::AddAnimation(const std::string& name, Animation* animation) {
    // Set initial animation.
    if (currentAnimation == nullptr) {
        currentAnimation = animation;
        const auto& frame = currentAnimation->GetCurrentFrame();
        sprite->SetRect(frame->x, frame->y, frame->width, frame->height);
    }
    
    animations.emplace(name, animation);
}

void SpriteAnimation::SetAnimation(const std::string& name) {
    auto iter = animations.find(name);
    if (iter != animations.end()) {
        currentAnimation = iter->second;
        currentAnimation->Reset();
    }
}
