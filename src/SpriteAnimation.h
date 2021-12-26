#pragma once

#include "Component.h"
#include <vector>
#include <map>
#include <string>

class Animation {
public:
    struct FrameData {
        int id;
        int x;
        int y;
        int width;
        int height;
        float displayTimeSeconds;
    };

    Animation() {}
    void AddFrame(int textureID, int x, int y, int width, int height, float frameTime);
    const FrameData* GetCurrentFrame() const;
    bool UpdateFrame(float deltaTime);
    void Reset();
    
private:
    std::vector<FrameData> frames;
    int currentFrameIndex = 0;
    float currentFrameTime = 0.0f;
};

class SpriteAnimation : public Component {
public:
    SpriteAnimation(class Actor* owner, class Texture* sheet);
    void Update(float deltaTime) override;
    void AddAnimation(const std::string& name, Animation* animation);
    void SetAnimation(const std::string& name);

private:
    class SpriteComponent* sprite = nullptr;
    Animation* currentAnimation = nullptr;;

    std::map<std::string, Animation*> animations;
};
