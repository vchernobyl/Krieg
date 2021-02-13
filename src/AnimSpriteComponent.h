#pragma once

#include "Actor.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
    void Update(float deltaTime) override;
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    float GetAnimFps() const { return animFps; }
    void SetAnimFps(float fps) { animFps = fps; }
private:
    std::vector<SDL_Texture*> animTextures;
    float currentFrame;
    float animFps;
};
